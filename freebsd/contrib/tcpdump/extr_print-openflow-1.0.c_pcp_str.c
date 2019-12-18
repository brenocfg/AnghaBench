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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

__attribute__((used)) static const char *
pcp_str(const uint8_t pcp)
{
	static char buf[sizeof("255 (bogus)")];
	snprintf(buf, sizeof(buf), pcp <= 7 ? "%u" : "%u (bogus)", pcp);
	return buf;
}