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
 int /*<<< orphan*/  EFFLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EFPRINTF (int /*<<< orphan*/ *,char*) ; 
 int errno ; 

__attribute__((used)) static int
basl_fwrite_facs(FILE *fp)
{
	EFPRINTF(fp, "/*\n");
	EFPRINTF(fp, " * bhyve FACS template\n");
	EFPRINTF(fp, " */\n");
	EFPRINTF(fp, "[0004]\t\tSignature : \"FACS\"\n");
	EFPRINTF(fp, "[0004]\t\tLength : 00000040\n");
	EFPRINTF(fp, "[0004]\t\tHardware Signature : 00000000\n");
	EFPRINTF(fp, "[0004]\t\t32 Firmware Waking Vector : 00000000\n");
	EFPRINTF(fp, "[0004]\t\tGlobal Lock : 00000000\n");
	EFPRINTF(fp, "[0004]\t\tFlags (decoded below) : 00000000\n");
	EFPRINTF(fp, "\t\t\tS4BIOS Support Present : 0\n");
	EFPRINTF(fp, "\t\t\t64-bit Wake Supported (V2) : 0\n");
	EFPRINTF(fp,
	    "[0008]\t\t64 Firmware Waking Vector : 0000000000000000\n");
	EFPRINTF(fp, "[0001]\t\tVersion : 02\n");
	EFPRINTF(fp, "[0003]\t\tReserved : 000000\n");
	EFPRINTF(fp, "[0004]\t\tOspmFlags (decoded below) : 00000000\n");
	EFPRINTF(fp, "\t\t\t64-bit Wake Env Required (V2) : 0\n");

	EFFLUSH(fp);

	return (0);
	
err_exit:
	return (errno);
}