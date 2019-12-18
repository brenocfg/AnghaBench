#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tm ;
struct tm {int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_5__ {int /*<<< orphan*/  d; scalar_t__ m; scalar_t__ y; } ;
typedef  TYPE_1__ date ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  D_MD_ORDER ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  easterg (int,TYPE_1__*) ; 
 int /*<<< orphan*/  easterog (int,TYPE_1__*) ; 
 int /*<<< orphan*/  easteroj (int,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static void
printeaster(int y, int julian, int orthodox)
{
	date    dt;
	struct tm tm;
	char    buf[MAX_WIDTH];
	static int d_first = -1;

	if (d_first < 0)
		d_first = (*nl_langinfo(D_MD_ORDER) == 'd');
	/* force orthodox easter for years before 1583 */
	if (y < 1583)
		orthodox = 1;

	if (orthodox)
		if (julian)
			easteroj(y, &dt);
		else
			easterog(y, &dt);
	else
		easterg(y, &dt);

	memset(&tm, 0, sizeof(tm));
	tm.tm_year = dt.y - 1900;
	tm.tm_mon  = dt.m - 1;
	tm.tm_mday = dt.d;
	strftime(buf, sizeof(buf), d_first ? "%e %B %Y" : "%B %e %Y",  &tm);
	printf("%s\n", buf);
}