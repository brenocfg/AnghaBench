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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr,
	"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
	"usage: bsdlabel disk",
	"\t\t(to read label)",
	"	bsdlabel -w [-n] [-m machine] disk [type]",
	"\t\t(to write label with existing boot program)",
	"	bsdlabel -e [-n] [-m machine] disk",
	"\t\t(to edit label)",
	"	bsdlabel -R [-n] [-m machine] disk protofile",
	"\t\t(to restore label with existing boot program)",
	"	bsdlabel -B [-b boot] [-m machine] disk",
	"\t\t(to install boot program with existing on-disk label)",
	"	bsdlabel -w -B [-n] [-b boot] [-m machine] disk [type]",
	"\t\t(to write label and install boot program)",
	"	bsdlabel -R -B [-n] [-b boot] [-m machine] disk protofile",
		"\t\t(to restore label and install boot program)"
	);
	exit(1);
}