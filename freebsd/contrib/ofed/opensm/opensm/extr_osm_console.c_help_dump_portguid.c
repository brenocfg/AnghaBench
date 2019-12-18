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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void help_dump_portguid(FILE * out, int detail)
{
	fprintf(out,
		"dump_portguid [file filename] regexp1 [regexp2 [regexp3 ...]] -- Dump port GUID matching a regexp \n");
	if (detail) {
		fprintf(out,
			"getguidgetguid  -- Dump all the port GUID whom node_desc matches one of the provided regexp\n");
		fprintf(out,
			"   [file filename] -- Send the port GUID list to the specified file instead of regular output\n");
	}

}