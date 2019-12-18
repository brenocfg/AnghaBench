#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct mips_tmp_reloc {int ahl; int* where_hi16; } ;
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int int16_t ;
typedef  int (* elf_lookup_fn ) (int /*<<< orphan*/ ,int,int,int*) ;
struct TYPE_4__ {int r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_3__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
typedef  int Elf_Word ;
typedef  TYPE_1__ Elf_Rela ;
typedef  TYPE_2__ Elf_Rel ;
typedef  int Elf_Addr ;
typedef  int Elf64_Addr ;
typedef  int Elf32_Addr ;

/* Variables and functions */
#define  ELF_RELOC_REL 137 
#define  ELF_RELOC_RELA 136 
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_MIPS_26 135 
#define  R_MIPS_32 134 
#define  R_MIPS_64 133 
#define  R_MIPS_HI16 132 
#define  R_MIPS_HIGHER 131 
#define  R_MIPS_HIGHEST 130 
#define  R_MIPS_LO16 129 
#define  R_MIPS_NONE 128 
 int /*<<< orphan*/  mips_tmp_reloc_add (int,int*) ; 
 int /*<<< orphan*/  mips_tmp_reloc_free (struct mips_tmp_reloc*) ; 
 struct mips_tmp_reloc* mips_tmp_reloc_get () ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
elf_reloc_internal(linker_file_t lf, Elf_Addr relocbase, const void *data,
    int type, int local, elf_lookup_fn lookup)
{
	Elf32_Addr *where = (Elf32_Addr *)NULL;
	Elf_Addr addr;
	Elf_Addr addend = (Elf_Addr)0;
	Elf_Word rtype = (Elf_Word)0, symidx;
	struct mips_tmp_reloc *r;
	const Elf_Rel *rel = NULL;
	const Elf_Rela *rela = NULL;
	int error;

	/* Store the last seen ahl from a HI16 for LO16 processing */
	static Elf_Addr last_ahl;

	switch (type) {
	case ELF_RELOC_REL:
		rel = (const Elf_Rel *)data;
		where = (Elf32_Addr *) (relocbase + rel->r_offset);
		rtype = ELF_R_TYPE(rel->r_info);
		symidx = ELF_R_SYM(rel->r_info);
		switch (rtype) {
		case R_MIPS_64:
			addend = *(Elf64_Addr *)where;
			break;
		default:
			addend = *where;
			break;
		}

		break;
	case ELF_RELOC_RELA:
		rela = (const Elf_Rela *)data;
		where = (Elf32_Addr *) (relocbase + rela->r_offset);
		addend = rela->r_addend;
		rtype = ELF_R_TYPE(rela->r_info);
		symidx = ELF_R_SYM(rela->r_info);
		break;
	default:
		panic("unknown reloc type %d\n", type);
	}

	switch (rtype) {
	case R_MIPS_NONE:	/* none */
		break;

	case R_MIPS_32:		/* S + A */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return (-1);
		addr += addend;
		if (*where != addr)
			*where = (Elf32_Addr)addr;
		break;

	case R_MIPS_26:		/* ((A << 2) | (P & 0xf0000000) + S) >> 2 */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return (-1);

		addend &= 0x03ffffff;
		/*
		 * Addendum for .rela R_MIPS_26 is not shifted right
		 */
		if (rela == NULL)
			addend <<= 2;

		addr += ((Elf_Addr)where & 0xf0000000) | addend;
		addr >>= 2;

		*where &= ~0x03ffffff;
		*where |= addr & 0x03ffffff;
		break;

	case R_MIPS_64:		/* S + A */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return (-1);
		addr += addend;
		if (*(Elf64_Addr*)where != addr)
			*(Elf64_Addr*)where = addr;
		break;

	/*
	 * Handle the two GNU extension cases:
	 *
	 * + Multiple HI16s followed by a LO16, and
	 * + A HI16 followed by multiple LO16s.
	 *
	 * The former is tricky - the HI16 relocations need
	 * to be buffered until a LO16 occurs, at which point
	 * each HI16 is replayed against the LO16 relocation entry
	 * (with the relevant overflow information.)
	 *
	 * The latter should be easy to handle - when the
	 * first LO16 is seen, write out and flush the
	 * HI16 buffer.  Any subsequent LO16 entries will
	 * find a blank relocation buffer.
	 *
	 */

	case R_MIPS_HI16:	/* ((AHL + S) - ((short)(AHL + S)) >> 16 */
		if (rela != NULL) {
			error = lookup(lf, symidx, 1, &addr);
			if (error != 0)
				return (-1);
			addr += addend;
			*where &= 0xffff0000;
			*where |= ((((long long) addr + 0x8000LL) >> 16) & 0xffff);
		} else {
			/*
			 * Add a temporary relocation to the list;
			 * will pop it off / free the list when
			 * we've found a suitable HI16.
			 */
			if (mips_tmp_reloc_add(addend << 16, where) == 0)
				return (-1);
			/*
			 * Track the last seen HI16 AHL for use by
			 * the first LO16 AHL calculation.
			 *
			 * The assumption is any intermediary deleted
			 * LO16's were optimised out, so the last
			 * HI16 before the LO16 is the "true" relocation
			 * entry to use for that LO16 write.
			 */
			last_ahl = addend << 16;
		}
		break;

	case R_MIPS_LO16:	/* AHL + S */
		if (rela != NULL) {
			error = lookup(lf, symidx, 1, &addr);
			if (error != 0)
				return (-1);
			addr += addend;
			*where &= 0xffff0000;
			*where |= addr & 0xffff;
		} else {
			Elf_Addr tmp_ahl;
			Elf_Addr tmp_addend;

			tmp_ahl = last_ahl + (int16_t) addend;
			error = lookup(lf, symidx, 1, &addr);
			if (error != 0)
				return (-1);

			tmp_addend = addend & 0xffff0000;

			/* Use the last seen ahl for calculating addend */
			tmp_addend |= (uint16_t)(tmp_ahl + addr);
			*where = tmp_addend;

			/*
			 * This logic implements the "we saw multiple HI16
			 * before a LO16" assignment /and/ "we saw multiple
			 * LO16s".
			 *
			 * Multiple LO16s will be handled as a blank
			 * relocation list.
			 *
			 * Multple HI16's are iterated over here.
			 */
			while ((r = mips_tmp_reloc_get()) != NULL) {
				Elf_Addr rahl;

				/*
				 * We have the ahl from the HI16 entry, so
				 * offset it by the 16 bits of the low ahl.
				 */
				rahl = r->ahl;
				rahl += (int16_t) addend;

				tmp_addend = *(r->where_hi16);
				tmp_addend &= 0xffff0000;
				tmp_addend |= ((rahl + addr) -
				    (int16_t)(rahl + addr)) >> 16;
				*(r->where_hi16) = tmp_addend;
				mips_tmp_reloc_free(r);
			}
		}

		break;

	case R_MIPS_HIGHER:	/* %higher(A+S) */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return (-1);
		addr += addend;
		*where &= 0xffff0000;
		*where |= (((long long)addr + 0x80008000LL) >> 32) & 0xffff;
		break;

	case R_MIPS_HIGHEST:	/* %highest(A+S) */
		error = lookup(lf, symidx, 1, &addr);
		if (error != 0)
			return (-1);
		addr += addend;
		*where &= 0xffff0000;
		*where |= (((long long)addr + 0x800080008000LL) >> 48) & 0xffff;
		break;

	default:
		printf("kldload: unexpected relocation type %d\n",
			rtype);
		return (-1);
	}

	return(0);
}