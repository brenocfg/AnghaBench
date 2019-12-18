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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  print_ext_speed (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_device_desc(u_char *p, int len, const char *type)
{
	static const char *un_name[] =
	{"512b", "2Kb", "8Kb", "32Kb", "128Kb", "512Kb", "2Mb", "reserved"};
	static const char *speed[] =
	{"No speed", "250nS", "200nS", "150nS",
	"100nS", "Reserved", "Reserved"};
	static const char *dev[] =
	{"No device", "Mask ROM", "OTPROM", "UV EPROM",
	 "EEPROM", "FLASH EEPROM", "SRAM", "DRAM",
	 "Reserved", "Reserved", "Reserved", "Reserved",
	 "Reserved", "Function specific", "Extended",
	"Reserved"};
	int     count = 0;

	while (*p != 0xFF && len > 0) {
		u_char x;

		x = *p++;
		len -= 2;
		if (count++ == 0)
			printf("\t%s memory device information:\n", type);
		printf("\t\tDevice number %d, type %s, WPS = %s\n",
		    count, dev[x >> 4], (x & 0x8) ? "ON" : "OFF");
		if ((x & 7) == 7) {
			len--;
			if (*p) {
				printf("\t\t");
				print_ext_speed(*p, 0);
				while (*p & 0x80) {
					p++;
					len--;
				}
			}
			p++;
		} else
			printf("\t\tSpeed = %s", speed[x & 7]);
		printf(", Memory block size = %s, %d units\n",
		    un_name[*p & 7], (*p >> 3) + 1);
		p++;
	}
}