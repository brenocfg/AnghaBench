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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  emit_relocs (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_reloc_info () ; 
 int /*<<< orphan*/  read_ehdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_relocs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_shdrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_strtabs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_symtabs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regex_init () ; 
 int /*<<< orphan*/  remove_relocs (int /*<<< orphan*/ *) ; 

void process(FILE *fp, int as_text, int as_bin,
	     int show_reloc_info, int keep_relocs)
{
	regex_init();
	read_ehdr(fp);
	read_shdrs(fp);
	read_strtabs(fp);
	read_symtabs(fp);
	read_relocs(fp);
	if (show_reloc_info) {
		print_reloc_info();
		return;
	}
	emit_relocs(as_text, as_bin, fp);
	if (!keep_relocs)
		remove_relocs(fp);
}