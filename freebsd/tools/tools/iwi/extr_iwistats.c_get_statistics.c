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
struct statistic {int index; char* desc; } ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  oid ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int sscanf (char const*,char*,int*) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct statistic* tbl ; 

__attribute__((used)) static void
get_statistics(const char *iface)
{
	static uint32_t stats[256];
	const struct statistic *stat;
	char oid[32];
	size_t len;
	int ifaceno;

	if (sscanf(iface, "iwi%u", &ifaceno) != 1)
		errx(EX_DATAERR, "Invalid interface name '%s'", iface);

	len = sizeof(stats);
	(void)snprintf(oid, sizeof(oid), "dev.iwi.%u.stats", ifaceno);
	if (sysctlbyname(oid, stats, &len, NULL, 0) == -1)
		err(EX_OSERR, "Can't retrieve statistics");

	for (stat = tbl; stat->index != -1; stat++)
		(void)printf("%-60s[%u]\n", stat->desc, stats[stat->index]);
}