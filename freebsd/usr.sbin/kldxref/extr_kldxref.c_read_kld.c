#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mod_metadata {scalar_t__ md_type; scalar_t__ md_cval; } ;
struct elf_file {int dummy; } ;
typedef  int /*<<< orphan*/  md ;
typedef  int /*<<< orphan*/  cval ;
typedef  int /*<<< orphan*/  Elf_Off ;

/* Variables and functions */
 int EFT_KERNEL ; 
 int EFT_KLD ; 
 int /*<<< orphan*/  EF_CLOSE (struct elf_file*) ; 
 int EF_GET_TYPE (struct elf_file*) ; 
 int /*<<< orphan*/  EF_LOOKUP_SET (struct elf_file*,int /*<<< orphan*/ ,long*,long*,long*) ; 
 int /*<<< orphan*/  EF_SEG_READ_ENTRY_REL (struct elf_file*,long,int,void*) ; 
 int /*<<< orphan*/  EF_SEG_READ_REL (struct elf_file*,int /*<<< orphan*/ ,int,struct mod_metadata*) ; 
 int /*<<< orphan*/  EF_SEG_READ_STRING (struct elf_file*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  MAXMODNAME ; 
 scalar_t__ MDT_MODULE ; 
 int /*<<< orphan*/  MDT_SETNAME ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/ ) ; 
 scalar_t__ dflag ; 
 int ef_obj_open (char*,struct elf_file*,scalar_t__) ; 
 int ef_open (char*,struct elf_file*,scalar_t__) ; 
 int /*<<< orphan*/  free (void**) ; 
 int /*<<< orphan*/  parse_entry (struct mod_metadata*,char*,struct elf_file*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warnc (int,char*,char*) ; 

__attribute__((used)) static int
read_kld(char *filename, char *kldname)
{
	struct mod_metadata md;
	struct elf_file ef;
	void **p;
	int error, eftype;
	long start, finish, entries, i;
	char cval[MAXMODNAME + 1];

	if (verbose || dflag)
		printf("%s\n", filename);
	error = ef_open(filename, &ef, verbose);
	if (error != 0) {
		error = ef_obj_open(filename, &ef, verbose);
		if (error != 0) {
			if (verbose)
				warnc(error, "elf_open(%s)", filename);
			return (error);
		}
	}
	eftype = EF_GET_TYPE(&ef);
	if (eftype != EFT_KLD && eftype != EFT_KERNEL)  {
		EF_CLOSE(&ef);
		return (0);
	}
	do {
		check(EF_LOOKUP_SET(&ef, MDT_SETNAME, &start, &finish,
		    &entries));
		check(EF_SEG_READ_ENTRY_REL(&ef, start, sizeof(*p) * entries,
		    (void *)&p));
		/*
		 * Do a first pass to find MDT_MODULE.  It is required to be
		 * ordered first in the output linker.hints stream because it
		 * serves as an implicit record boundary between distinct klds
		 * in the stream.  Other MDTs only make sense in the context of
		 * a specific MDT_MODULE.
		 *
		 * Some compilers (e.g., GCC 6.4.0 xtoolchain) or binutils
		 * (e.g., GNU binutils 2.32 objcopy/ld.bfd) can reorder
		 * MODULE_METADATA set entries relative to the source ordering.
		 * This is permitted by the C standard; memory layout of
		 * file-scope objects is left implementation-defined.  There is
		 * no requirement that source code ordering is retained.
		 *
		 * Handle that here by taking two passes to ensure MDT_MODULE
		 * records are emitted to linker.hints before other MDT records
		 * in the same kld.
		 */
		for (i = 0; i < entries; i++) {
			check(EF_SEG_READ_REL(&ef, (Elf_Off)p[i], sizeof(md),
			    &md));
			check(EF_SEG_READ_STRING(&ef, (Elf_Off)md.md_cval,
			    sizeof(cval), cval));
			if (md.md_type == MDT_MODULE) {
				parse_entry(&md, cval, &ef, kldname);
				break;
			}
		}
		if (error != 0) {
			warnc(error, "error while reading %s", filename);
			break;
		}

		/*
		 * Second pass for all !MDT_MODULE entries.
		 */
		for (i = 0; i < entries; i++) {
			check(EF_SEG_READ_REL(&ef, (Elf_Off)p[i], sizeof(md),
			    &md));
			check(EF_SEG_READ_STRING(&ef, (Elf_Off)md.md_cval,
			    sizeof(cval), cval));
			if (md.md_type != MDT_MODULE)
				parse_entry(&md, cval, &ef, kldname);
		}
		if (error != 0)
			warnc(error, "error while reading %s", filename);
		free(p);
	} while(0);
	EF_CLOSE(&ef);
	return (error);
}