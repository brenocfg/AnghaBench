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
 int /*<<< orphan*/  EFPRINTF (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  SCI_INT ; 
 int basl_ncpu ; 
 int errno ; 

__attribute__((used)) static int
basl_fwrite_madt(FILE *fp)
{
	int i;

	EFPRINTF(fp, "/*\n");
	EFPRINTF(fp, " * bhyve MADT template\n");
	EFPRINTF(fp, " */\n");
	EFPRINTF(fp, "[0004]\t\tSignature : \"APIC\"\n");
	EFPRINTF(fp, "[0004]\t\tTable Length : 00000000\n");
	EFPRINTF(fp, "[0001]\t\tRevision : 01\n");
	EFPRINTF(fp, "[0001]\t\tChecksum : 00\n");
	EFPRINTF(fp, "[0006]\t\tOem ID : \"BHYVE \"\n");
	EFPRINTF(fp, "[0008]\t\tOem Table ID : \"BVMADT  \"\n");
	EFPRINTF(fp, "[0004]\t\tOem Revision : 00000001\n");

	/* iasl will fill in the compiler ID/revision fields */
	EFPRINTF(fp, "[0004]\t\tAsl Compiler ID : \"xxxx\"\n");
	EFPRINTF(fp, "[0004]\t\tAsl Compiler Revision : 00000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0004]\t\tLocal Apic Address : FEE00000\n");
	EFPRINTF(fp, "[0004]\t\tFlags (decoded below) : 00000001\n");
	EFPRINTF(fp, "\t\t\tPC-AT Compatibility : 1\n");
	EFPRINTF(fp, "\n");

	/* Add a Processor Local APIC entry for each CPU */
	for (i = 0; i < basl_ncpu; i++) {
		EFPRINTF(fp, "[0001]\t\tSubtable Type : 00\n");
		EFPRINTF(fp, "[0001]\t\tLength : 08\n");
		/* iasl expects hex values for the proc and apic id's */
		EFPRINTF(fp, "[0001]\t\tProcessor ID : %02x\n", i);
		EFPRINTF(fp, "[0001]\t\tLocal Apic ID : %02x\n", i);
		EFPRINTF(fp, "[0004]\t\tFlags (decoded below) : 00000001\n");
		EFPRINTF(fp, "\t\t\tProcessor Enabled : 1\n");
		EFPRINTF(fp, "\t\t\tRuntime Online Capable : 0\n");
		EFPRINTF(fp, "\n");
	}

	/* Always a single IOAPIC entry, with ID 0 */
	EFPRINTF(fp, "[0001]\t\tSubtable Type : 01\n");
	EFPRINTF(fp, "[0001]\t\tLength : 0C\n");
	/* iasl expects a hex value for the i/o apic id */
	EFPRINTF(fp, "[0001]\t\tI/O Apic ID : %02x\n", 0);
	EFPRINTF(fp, "[0001]\t\tReserved : 00\n");
	EFPRINTF(fp, "[0004]\t\tAddress : fec00000\n");
	EFPRINTF(fp, "[0004]\t\tInterrupt : 00000000\n");
	EFPRINTF(fp, "\n");

	/* Legacy IRQ0 is connected to pin 2 of the IOAPIC */
	EFPRINTF(fp, "[0001]\t\tSubtable Type : 02\n");
	EFPRINTF(fp, "[0001]\t\tLength : 0A\n");
	EFPRINTF(fp, "[0001]\t\tBus : 00\n");
	EFPRINTF(fp, "[0001]\t\tSource : 00\n");
	EFPRINTF(fp, "[0004]\t\tInterrupt : 00000002\n");
	EFPRINTF(fp, "[0002]\t\tFlags (decoded below) : 0005\n");
	EFPRINTF(fp, "\t\t\tPolarity : 1\n");
	EFPRINTF(fp, "\t\t\tTrigger Mode : 1\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0001]\t\tSubtable Type : 02\n");
	EFPRINTF(fp, "[0001]\t\tLength : 0A\n");
	EFPRINTF(fp, "[0001]\t\tBus : 00\n");
	EFPRINTF(fp, "[0001]\t\tSource : %02X\n", SCI_INT);
	EFPRINTF(fp, "[0004]\t\tInterrupt : %08X\n", SCI_INT);
	EFPRINTF(fp, "[0002]\t\tFlags (decoded below) : 0000\n");
	EFPRINTF(fp, "\t\t\tPolarity : 3\n");
	EFPRINTF(fp, "\t\t\tTrigger Mode : 3\n");
	EFPRINTF(fp, "\n");

	/* Local APIC NMI is connected to LINT 1 on all CPUs */
	EFPRINTF(fp, "[0001]\t\tSubtable Type : 04\n");
	EFPRINTF(fp, "[0001]\t\tLength : 06\n");
	EFPRINTF(fp, "[0001]\t\tProcessor ID : FF\n");
	EFPRINTF(fp, "[0002]\t\tFlags (decoded below) : 0005\n");
	EFPRINTF(fp, "\t\t\tPolarity : 1\n");
	EFPRINTF(fp, "\t\t\tTrigger Mode : 1\n");
	EFPRINTF(fp, "[0001]\t\tInterrupt Input LINT : 01\n");
	EFPRINTF(fp, "\n");

	EFFLUSH(fp);

	return (0);

err_exit:
	return (errno);
}