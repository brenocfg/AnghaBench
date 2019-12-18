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
 int /*<<< orphan*/  BHYVE_ACPI_DISABLE ; 
 int /*<<< orphan*/  BHYVE_ACPI_ENABLE ; 
 scalar_t__ DSDT_OFFSET ; 
 int /*<<< orphan*/  EFFLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EFPRINTF (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ FACS_OFFSET ; 
 int /*<<< orphan*/  IO_PMTMR ; 
 int /*<<< orphan*/  PM1A_CNT_ADDR ; 
 int /*<<< orphan*/  PM1A_EVT_ADDR ; 
 int /*<<< orphan*/  SCI_INT ; 
 int /*<<< orphan*/  SMI_CMD ; 
 scalar_t__ basl_acpi_base ; 
 int errno ; 

__attribute__((used)) static int
basl_fwrite_fadt(FILE *fp)
{
	EFPRINTF(fp, "/*\n");
	EFPRINTF(fp, " * bhyve FADT template\n");
	EFPRINTF(fp, " */\n");
	EFPRINTF(fp, "[0004]\t\tSignature : \"FACP\"\n");
	EFPRINTF(fp, "[0004]\t\tTable Length : 0000010C\n");
	EFPRINTF(fp, "[0001]\t\tRevision : 05\n");
	EFPRINTF(fp, "[0001]\t\tChecksum : 00\n");
	EFPRINTF(fp, "[0006]\t\tOem ID : \"BHYVE \"\n");
	EFPRINTF(fp, "[0008]\t\tOem Table ID : \"BVFACP  \"\n");
	EFPRINTF(fp, "[0004]\t\tOem Revision : 00000001\n");
	/* iasl will fill in the compiler ID/revision fields */
	EFPRINTF(fp, "[0004]\t\tAsl Compiler ID : \"xxxx\"\n");
	EFPRINTF(fp, "[0004]\t\tAsl Compiler Revision : 00000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0004]\t\tFACS Address : %08X\n",
	    basl_acpi_base + FACS_OFFSET);
	EFPRINTF(fp, "[0004]\t\tDSDT Address : %08X\n",
	    basl_acpi_base + DSDT_OFFSET);
	EFPRINTF(fp, "[0001]\t\tModel : 01\n");
	EFPRINTF(fp, "[0001]\t\tPM Profile : 00 [Unspecified]\n");
	EFPRINTF(fp, "[0002]\t\tSCI Interrupt : %04X\n",
	    SCI_INT);
	EFPRINTF(fp, "[0004]\t\tSMI Command Port : %08X\n",
	    SMI_CMD);
	EFPRINTF(fp, "[0001]\t\tACPI Enable Value : %02X\n",
	    BHYVE_ACPI_ENABLE);
	EFPRINTF(fp, "[0001]\t\tACPI Disable Value : %02X\n",
	    BHYVE_ACPI_DISABLE);
	EFPRINTF(fp, "[0001]\t\tS4BIOS Command : 00\n");
	EFPRINTF(fp, "[0001]\t\tP-State Control : 00\n");
	EFPRINTF(fp, "[0004]\t\tPM1A Event Block Address : %08X\n",
	    PM1A_EVT_ADDR);
	EFPRINTF(fp, "[0004]\t\tPM1B Event Block Address : 00000000\n");
	EFPRINTF(fp, "[0004]\t\tPM1A Control Block Address : %08X\n",
	    PM1A_CNT_ADDR);
	EFPRINTF(fp, "[0004]\t\tPM1B Control Block Address : 00000000\n");
	EFPRINTF(fp, "[0004]\t\tPM2 Control Block Address : 00000000\n");
	EFPRINTF(fp, "[0004]\t\tPM Timer Block Address : %08X\n",
	    IO_PMTMR);
	EFPRINTF(fp, "[0004]\t\tGPE0 Block Address : 00000000\n");
	EFPRINTF(fp, "[0004]\t\tGPE1 Block Address : 00000000\n");
	EFPRINTF(fp, "[0001]\t\tPM1 Event Block Length : 04\n");
	EFPRINTF(fp, "[0001]\t\tPM1 Control Block Length : 02\n");
	EFPRINTF(fp, "[0001]\t\tPM2 Control Block Length : 00\n");
	EFPRINTF(fp, "[0001]\t\tPM Timer Block Length : 04\n");
	EFPRINTF(fp, "[0001]\t\tGPE0 Block Length : 00\n");
	EFPRINTF(fp, "[0001]\t\tGPE1 Block Length : 00\n");
	EFPRINTF(fp, "[0001]\t\tGPE1 Base Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\t_CST Support : 00\n");
	EFPRINTF(fp, "[0002]\t\tC2 Latency : 0000\n");
	EFPRINTF(fp, "[0002]\t\tC3 Latency : 0000\n");
	EFPRINTF(fp, "[0002]\t\tCPU Cache Size : 0000\n");
	EFPRINTF(fp, "[0002]\t\tCache Flush Stride : 0000\n");
	EFPRINTF(fp, "[0001]\t\tDuty Cycle Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\tDuty Cycle Width : 00\n");
	EFPRINTF(fp, "[0001]\t\tRTC Day Alarm Index : 00\n");
	EFPRINTF(fp, "[0001]\t\tRTC Month Alarm Index : 00\n");
	EFPRINTF(fp, "[0001]\t\tRTC Century Index : 32\n");
	EFPRINTF(fp, "[0002]\t\tBoot Flags (decoded below) : 0000\n");
	EFPRINTF(fp, "\t\t\tLegacy Devices Supported (V2) : 0\n");
	EFPRINTF(fp, "\t\t\t8042 Present on ports 60/64 (V2) : 0\n");
	EFPRINTF(fp, "\t\t\tVGA Not Present (V4) : 1\n");
	EFPRINTF(fp, "\t\t\tMSI Not Supported (V4) : 0\n");
	EFPRINTF(fp, "\t\t\tPCIe ASPM Not Supported (V4) : 1\n");
	EFPRINTF(fp, "\t\t\tCMOS RTC Not Present (V5) : 0\n");
	EFPRINTF(fp, "[0001]\t\tReserved : 00\n");
	EFPRINTF(fp, "[0004]\t\tFlags (decoded below) : 00000000\n");
	EFPRINTF(fp, "\t\t\tWBINVD instruction is operational (V1) : 1\n");
	EFPRINTF(fp, "\t\t\tWBINVD flushes all caches (V1) : 0\n");
	EFPRINTF(fp, "\t\t\tAll CPUs support C1 (V1) : 1\n");
	EFPRINTF(fp, "\t\t\tC2 works on MP system (V1) : 0\n");
	EFPRINTF(fp, "\t\t\tControl Method Power Button (V1) : 0\n");
	EFPRINTF(fp, "\t\t\tControl Method Sleep Button (V1) : 1\n");
	EFPRINTF(fp, "\t\t\tRTC wake not in fixed reg space (V1) : 0\n");
	EFPRINTF(fp, "\t\t\tRTC can wake system from S4 (V1) : 0\n");
	EFPRINTF(fp, "\t\t\t32-bit PM Timer (V1) : 1\n");
	EFPRINTF(fp, "\t\t\tDocking Supported (V1) : 0\n");
	EFPRINTF(fp, "\t\t\tReset Register Supported (V2) : 1\n");
	EFPRINTF(fp, "\t\t\tSealed Case (V3) : 0\n");
	EFPRINTF(fp, "\t\t\tHeadless - No Video (V3) : 1\n");
	EFPRINTF(fp, "\t\t\tUse native instr after SLP_TYPx (V3) : 0\n");
	EFPRINTF(fp, "\t\t\tPCIEXP_WAK Bits Supported (V4) : 0\n");
	EFPRINTF(fp, "\t\t\tUse Platform Timer (V4) : 0\n");
	EFPRINTF(fp, "\t\t\tRTC_STS valid on S4 wake (V4) : 0\n");
	EFPRINTF(fp, "\t\t\tRemote Power-on capable (V4) : 0\n");
	EFPRINTF(fp, "\t\t\tUse APIC Cluster Model (V4) : 0\n");
	EFPRINTF(fp, "\t\t\tUse APIC Physical Destination Mode (V4) : 1\n");
	EFPRINTF(fp, "\t\t\tHardware Reduced (V5) : 0\n");
	EFPRINTF(fp, "\t\t\tLow Power S0 Idle (V5) : 0\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp,
	    "[0012]\t\tReset Register : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 08\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\tEncoded Access Width : 01 [Byte Access:8]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000CF9\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0001]\t\tValue to cause reset : 06\n");
	EFPRINTF(fp, "[0002]\t\tARM Flags (decoded below): 0000\n");
	EFPRINTF(fp, "\t\t\tPSCI Compliant : 0\n");
	EFPRINTF(fp, "\t\t\tMust use HVC for PSCI : 0\n");
	EFPRINTF(fp, "[0001]\t\tFADT Minor Revision : 01\n");
	EFPRINTF(fp, "[0008]\t\tFACS Address : 00000000%08X\n",
	    basl_acpi_base + FACS_OFFSET);
	EFPRINTF(fp, "[0008]\t\tDSDT Address : 00000000%08X\n",
	    basl_acpi_base + DSDT_OFFSET);
	EFPRINTF(fp,
	    "[0012]\t\tPM1A Event Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 20\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\tEncoded Access Width : 02 [Word Access:16]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 00000000%08X\n",
	    PM1A_EVT_ADDR);
	EFPRINTF(fp, "\n");
	
	EFPRINTF(fp,
	    "[0012]\t\tPM1B Event Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 00\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp,
	    "[0001]\t\tEncoded Access Width : 00 [Undefined/Legacy]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp,
	    "[0012]\t\tPM1A Control Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 10\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\tEncoded Access Width : 02 [Word Access:16]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 00000000%08X\n",
	    PM1A_CNT_ADDR);
	EFPRINTF(fp, "\n");

	EFPRINTF(fp,
	    "[0012]\t\tPM1B Control Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 00\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp,
	    "[0001]\t\tEncoded Access Width : 00 [Undefined/Legacy]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp,
	    "[0012]\t\tPM2 Control Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 08\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp,
	    "[0001]\t\tEncoded Access Width : 00 [Undefined/Legacy]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000000\n");
	EFPRINTF(fp, "\n");

	/* Valid for bhyve */
	EFPRINTF(fp,
	    "[0012]\t\tPM Timer Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 20\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp,
	    "[0001]\t\tEncoded Access Width : 03 [DWord Access:32]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 00000000%08X\n",
	    IO_PMTMR);
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0012]\t\tGPE0 Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 00\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\tEncoded Access Width : 01 [Byte Access:8]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0012]\t\tGPE1 Block : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 00\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp,
	    "[0001]\t\tEncoded Access Width : 00 [Undefined/Legacy]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp,
	   "[0012]\t\tSleep Control Register : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 08\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\tEncoded Access Width : 01 [Byte Access:8]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp,
	    "[0012]\t\tSleep Status Register : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 01 [SystemIO]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 08\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp, "[0001]\t\tEncoded Access Width : 01 [Byte Access:8]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 0000000000000000\n");

	EFFLUSH(fp);

	return (0);

err_exit:
	return (errno);
}