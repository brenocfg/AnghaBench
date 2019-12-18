#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int time_t ;
struct tm {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct apm_pwstatus {int ap_device; int ap_batt_flag; int eax; int ecx; int edx; int esi; void* ebx; int /*<<< orphan*/  edi; int /*<<< orphan*/  ap_batt_time; int /*<<< orphan*/  ap_batt_life; int /*<<< orphan*/  ap_batt_stat; } ;
struct apm_bios_arg {int ap_device; int ap_batt_flag; int eax; int ecx; int edx; int esi; void* ebx; int /*<<< orphan*/  edi; int /*<<< orphan*/  ap_batt_time; int /*<<< orphan*/  ap_batt_life; int /*<<< orphan*/  ap_batt_stat; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  aps ;
typedef  TYPE_1__* apm_info_t ;
struct TYPE_3__ {int ai_major; int ai_minor; int ai_acline; int ai_infoversion; unsigned int ai_batteries; int ai_capabilities; int /*<<< orphan*/  ai_batt_time; int /*<<< orphan*/  ai_batt_life; int /*<<< orphan*/  ai_batt_stat; scalar_t__ ai_status; } ;

/* Variables and functions */
 int APMERR (int) ; 
 int /*<<< orphan*/  APMIO_BIOS ; 
 int /*<<< orphan*/  APMIO_GETPWSTATUS ; 
 int APM_BATT_NOT_PRESENT ; 
 int APM_BIOS ; 
 int APM_RESUMEONRING ; 
 int APM_RESUMETIMER ; 
 int APM_UNKNOWN ; 
 void* PMDV_APMBIOS ; 
 int PMDV_BATT0 ; 
 void* bcd2int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct apm_pwstatus*,int) ; 
 scalar_t__ cmos_wall ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct apm_pwstatus*) ; 
 struct tm* localtime (int*) ; 
 int mktime (struct tm*) ; 
 int /*<<< orphan*/  print_batt_life (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_batt_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_batt_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int timegm (struct tm*) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 
 int /*<<< orphan*/  xh (int) ; 
 int /*<<< orphan*/  xl (int) ; 

__attribute__((used)) static void 
print_all_info(int fd, apm_info_t aip, int bioscall_available)
{
	struct apm_bios_arg args;
	int apmerr;
	const char *line_msg[] = { "off-line", "on-line" , "backup power"};

	printf("APM version: %d.%d\n", aip->ai_major, aip->ai_minor);
	printf("APM Management: %s\n", aip->ai_status ? "Enabled" : "Disabled");
	printf("AC Line status: ");
	if (aip->ai_acline == APM_UNKNOWN)
		printf("unknown\n");
	else if (aip->ai_acline > 2)
		printf("invalid value (0x%x)\n", aip->ai_acline);
	else
		printf("%s\n", line_msg[aip->ai_acline]);

	print_batt_stat(aip->ai_batt_stat);
	print_batt_life(aip->ai_batt_life);
	print_batt_time(aip->ai_batt_time);

	if (aip->ai_infoversion >= 1) {
		printf("Number of batteries: ");
		if (aip->ai_batteries == ~0U)
			printf("unknown\n");
		else {
			u_int i;
			struct apm_pwstatus aps;

			printf("%d\n", aip->ai_batteries);
			for (i = 0; i < aip->ai_batteries; ++i) {
				bzero(&aps, sizeof(aps));
				aps.ap_device = PMDV_BATT0 + i;
				if (ioctl(fd, APMIO_GETPWSTATUS, &aps) == -1)
					continue;
				printf("Battery %d:\n", i);
				if (aps.ap_batt_flag & APM_BATT_NOT_PRESENT) {
					printf("not present\n");
					continue;
				}
				printf("\t");
				print_batt_stat(aps.ap_batt_stat);
				printf("\t");
				print_batt_life(aps.ap_batt_life);
				printf("\t");
				print_batt_time(aps.ap_batt_time);
			}
		}
	}

	if (bioscall_available) {
		/*
		 * try to get the suspend timer
		 */
		bzero(&args, sizeof(args));
		args.eax = (APM_BIOS) << 8 | APM_RESUMETIMER;
		args.ebx = PMDV_APMBIOS;
		args.ecx = 0x0001;
		if (ioctl(fd, APMIO_BIOS, &args)) {
			printf("Resume timer: unknown\n");
		} else {
			apmerr = APMERR(args.eax);
			if (apmerr == 0x0d || apmerr == 0x86)
				printf("Resume timer: disabled\n");
			else if (apmerr)
				warnx(
		"failed to get the resume timer: APM error0x%x", apmerr);
			else {
				/*
				 * OK.  We have the time (all bcd).
				 * CH - seconds
				 * DH - hours
				 * DL - minutes
				 * xh(SI) - month (1-12)
				 * xl(SI) - day of month (1-31)
				 * DI - year
				 */
				struct tm tm;
				char buf[1024];
				time_t t;

				tm.tm_sec = bcd2int(xh(args.ecx));
				tm.tm_min = bcd2int(xl(args.edx));
				tm.tm_hour = bcd2int(xh(args.edx));
				tm.tm_mday = bcd2int(xl(args.esi));
				tm.tm_mon = bcd2int(xh(args.esi)) - 1;
				tm.tm_year = bcd2int(args.edi) - 1900;
				if (cmos_wall)
					t = mktime(&tm);
				else
					t = timegm(&tm);
				if (t != -1) {
					tm = *localtime(&t);
					strftime(buf, sizeof(buf), "%c", &tm);
					printf("Resume timer: %s\n", buf);
				} else
					printf("Resume timer: unknown\n");
			}
		}

		/*
		 * Get the ring indicator resume state
		 */
		bzero(&args, sizeof(args));
		args.eax  = (APM_BIOS) << 8 | APM_RESUMEONRING;
		args.ebx = PMDV_APMBIOS;
		args.ecx = 0x0002;
		if (ioctl(fd, APMIO_BIOS, &args) == 0) {
			printf("Resume on ring indicator: %sabled\n",
			    args.ecx ? "en" : "dis");
		}
	}

	if (aip->ai_infoversion >= 1) {
		if (aip->ai_capabilities == 0xff00)
		    return;
		printf("APM Capabilities:\n");
		if (aip->ai_capabilities & 0x01)
			printf("\tglobal standby state\n");
		if (aip->ai_capabilities & 0x02)
			printf("\tglobal suspend state\n");
		if (aip->ai_capabilities & 0x04)
			printf("\tresume timer from standby\n");
		if (aip->ai_capabilities & 0x08)
			printf("\tresume timer from suspend\n");
		if (aip->ai_capabilities & 0x10)
			printf("\tRI resume from standby\n");
		if (aip->ai_capabilities & 0x20)
			printf("\tRI resume from suspend\n");
		if (aip->ai_capabilities & 0x40)
			printf("\tPCMCIA RI resume from standby\n");
		if (aip->ai_capabilities & 0x80)
			printf("\tPCMCIA RI resume from suspend\n");
	}

}