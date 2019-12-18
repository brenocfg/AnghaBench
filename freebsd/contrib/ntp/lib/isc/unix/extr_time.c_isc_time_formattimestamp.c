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
typedef  scalar_t__ time_t ;
struct TYPE_3__ {int nanoseconds; scalar_t__ seconds; } ;
typedef  TYPE_1__ isc_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  localtime (scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,...) ; 
 unsigned int strftime (char*,unsigned int,char*,int /*<<< orphan*/ ) ; 

void
isc_time_formattimestamp(const isc_time_t *t, char *buf, unsigned int len) {
	time_t now;
	unsigned int flen;

	REQUIRE(len > 0);

	now = (time_t) t->seconds;
	flen = strftime(buf, len, "%d-%b-%Y %X", localtime(&now));
	INSIST(flen < len);
	if (flen != 0)
		snprintf(buf + flen, len - flen,
			 ".%03u", t->nanoseconds / 1000000);
	else
		snprintf(buf, len, "99-Bad-9999 99:99:99.999");
}