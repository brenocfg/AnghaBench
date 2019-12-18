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
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

void mad_dump_portcapmask(char *buf, int bufsz, void *val, int valsz)
{
	unsigned mask = *(unsigned *)val;
	char *s = buf;

	s += sprintf(s, "0x%x\n", mask);
	if (mask & (1 << 1))
		s += sprintf(s, "\t\t\t\tIsSM\n");
	if (mask & (1 << 2))
		s += sprintf(s, "\t\t\t\tIsNoticeSupported\n");
	if (mask & (1 << 3))
		s += sprintf(s, "\t\t\t\tIsTrapSupported\n");
	if (mask & (1 << 4))
		s += sprintf(s, "\t\t\t\tIsOptionalIPDSupported\n");
	if (mask & (1 << 5))
		s += sprintf(s, "\t\t\t\tIsAutomaticMigrationSupported\n");
	if (mask & (1 << 6))
		s += sprintf(s, "\t\t\t\tIsSLMappingSupported\n");
	if (mask & (1 << 7))
		s += sprintf(s, "\t\t\t\tIsMKeyNVRAM\n");
	if (mask & (1 << 8))
		s += sprintf(s, "\t\t\t\tIsPKeyNVRAM\n");
	if (mask & (1 << 9))
		s += sprintf(s, "\t\t\t\tIsLedInfoSupported\n");
	if (mask & (1 << 10))
		s += sprintf(s, "\t\t\t\tIsSMdisabled\n");
	if (mask & (1 << 11))
		s += sprintf(s, "\t\t\t\tIsSystemImageGUIDsupported\n");
	if (mask & (1 << 12))
		s += sprintf(s,
			     "\t\t\t\tIsPkeySwitchExternalPortTrapSupported\n");
	if (mask & (1 << 14))
		s += sprintf(s, "\t\t\t\tIsExtendedSpeedsSupported\n");
	if (mask & (1 << 15))
		s += sprintf(s, "\t\t\t\tIsCapabilityMask2Supported\n");
	if (mask & (1 << 16))
		s += sprintf(s, "\t\t\t\tIsCommunicatonManagementSupported\n");
	if (mask & (1 << 17))
		s += sprintf(s, "\t\t\t\tIsSNMPTunnelingSupported\n");
	if (mask & (1 << 18))
		s += sprintf(s, "\t\t\t\tIsReinitSupported\n");
	if (mask & (1 << 19))
		s += sprintf(s, "\t\t\t\tIsDeviceManagementSupported\n");
	if (mask & (1 << 20))
		s += sprintf(s, "\t\t\t\tIsVendorClassSupported\n");
	if (mask & (1 << 21))
		s += sprintf(s, "\t\t\t\tIsDRNoticeSupported\n");
	if (mask & (1 << 22))
		s += sprintf(s, "\t\t\t\tIsCapabilityMaskNoticeSupported\n");
	if (mask & (1 << 23))
		s += sprintf(s, "\t\t\t\tIsBootManagementSupported\n");
	if (mask & (1 << 24))
		s += sprintf(s, "\t\t\t\tIsLinkRoundTripLatencySupported\n");
	if (mask & (1 << 25))
		s += sprintf(s, "\t\t\t\tIsClientRegistrationSupported\n");
	if (mask & (1 << 26))
		s += sprintf(s, "\t\t\t\tIsOtherLocalChangesNoticeSupported\n");
	if (mask & (1 << 27))
		s += sprintf(s,
			     "\t\t\t\tIsLinkSpeedWidthPairsTableSupported\n");
	if (mask & (1 << 28))
		s += sprintf(s, "\t\t\t\tIsVendorSpecificMadsTableSupported\n");
	if (mask & (1 << 29))
		s += sprintf(s, "\t\t\t\tIsMcastPkeyTrapSuppressionSupported\n");
	if (mask & (1 << 30))
		s += sprintf(s, "\t\t\t\tIsMulticastFDBTopSupported\n");
	if (mask & (1 << 31))
		s += sprintf(s, "\t\t\t\tIsHierarchyInfoSupported\n");

	if (s != buf)
		*(--s) = 0;
}