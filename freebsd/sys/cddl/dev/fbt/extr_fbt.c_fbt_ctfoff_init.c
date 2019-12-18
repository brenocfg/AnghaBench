#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {char* pathname; } ;
typedef  TYPE_1__ modctl_t ;
struct TYPE_8__ {int nsym; int** ctfoffp; TYPE_4__* symtab; int /*<<< orphan*/ * ctftab; } ;
typedef  TYPE_2__ linker_ctf_t ;
struct TYPE_9__ {int cth_objtoff; int cth_funcoff; scalar_t__ cth_magic; int cth_typeoff; } ;
typedef  TYPE_3__ ctf_header_t ;
struct TYPE_10__ {scalar_t__ st_name; scalar_t__ st_shndx; int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_4__ Elf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_INFO_VLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_K_UNKNOWN ; 
 scalar_t__ CTF_MAGIC ; 
 int EINVAL ; 
 int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LINKER ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ SHN_ABS ; 
 scalar_t__ SHN_UNDEF ; 
#define  STT_FUNC 129 
#define  STT_OBJECT 128 
 int* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
fbt_ctfoff_init(modctl_t *lf, linker_ctf_t *lc)
{
	const Elf_Sym *symp = lc->symtab;;
	const ctf_header_t *hp = (const ctf_header_t *) lc->ctftab;
	const uint8_t *ctfdata = lc->ctftab + sizeof(ctf_header_t);
	int i;
	uint32_t *ctfoff;
	uint32_t objtoff = hp->cth_objtoff;
	uint32_t funcoff = hp->cth_funcoff;
	ushort_t info;
	ushort_t vlen;

	/* Sanity check. */
	if (hp->cth_magic != CTF_MAGIC) {
		printf("Bad magic value in CTF data of '%s'\n",lf->pathname);
		return (EINVAL);
	}

	if (lc->symtab == NULL) {
		printf("No symbol table in '%s'\n",lf->pathname);
		return (EINVAL);
	}

	ctfoff = malloc(sizeof(uint32_t) * lc->nsym, M_LINKER, M_WAITOK);
	*lc->ctfoffp = ctfoff;

	for (i = 0; i < lc->nsym; i++, ctfoff++, symp++) {
		if (symp->st_name == 0 || symp->st_shndx == SHN_UNDEF) {
			*ctfoff = 0xffffffff;
			continue;
		}

		switch (ELF_ST_TYPE(symp->st_info)) {
		case STT_OBJECT:
			if (objtoff >= hp->cth_funcoff ||
                            (symp->st_shndx == SHN_ABS && symp->st_value == 0)) {
				*ctfoff = 0xffffffff;
                                break;
                        }

                        *ctfoff = objtoff;
                        objtoff += sizeof (ushort_t);
			break;

		case STT_FUNC:
			if (funcoff >= hp->cth_typeoff) {
				*ctfoff = 0xffffffff;
				break;
			}

			*ctfoff = funcoff;

			info = *((const ushort_t *)(ctfdata + funcoff));
			vlen = CTF_INFO_VLEN(info);

			/*
			 * If we encounter a zero pad at the end, just skip it.
			 * Otherwise skip over the function and its return type
			 * (+2) and the argument list (vlen).
			 */
			if (CTF_INFO_KIND(info) == CTF_K_UNKNOWN && vlen == 0)
				funcoff += sizeof (ushort_t); /* skip pad */
			else
				funcoff += sizeof (ushort_t) * (vlen + 2);
			break;

		default:
			*ctfoff = 0xffffffff;
			break;
		}
	}

	return (0);
}