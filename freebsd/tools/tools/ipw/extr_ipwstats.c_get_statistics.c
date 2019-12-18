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
typedef  int uint32_t ;
struct statistic {scalar_t__ index; char* desc; int unit; } ;

/* Variables and functions */
#define  BOOL 131 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
#define  HEX 130 
#define  INT 129 
#define  PERCENTAGE 128 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int sscanf (char const*,char*,int*) ; 
 int sysctlbyname (char*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct statistic* tbl ; 

__attribute__((used)) static void
get_statistics(const char *iface)
{
	static uint32_t stats[256];
	const struct statistic *stat;
	char oid[32];
	int ifaceno, len;

	if (sscanf(iface, "ipw%u", &ifaceno) != 1)
		errx(EX_DATAERR, "Invalid interface name '%s'", iface);

	len = sizeof stats;
	snprintf(oid, sizeof oid, "dev.ipw.%u.stats", ifaceno);
	if (sysctlbyname(oid, stats, &len, NULL, 0) == -1)
		err(EX_OSERR, "Can't retrieve statistics");

	for (stat = tbl; stat->index != 0; stat++) {
		printf("%-60s[", stat->desc);
		switch (stat->unit) {
		case INT:
			printf("%u", stats[stat->index]);
			break;
		case BOOL:
			printf(stats[stat->index] ? "true" : "false");
			break;
		case PERCENTAGE:
			printf("%u%%", stats[stat->index]);
			break;
		case HEX:
		default:
			printf("0x%08X", stats[stat->index]);
		}
		printf("]\n");
	}
}