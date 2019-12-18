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
typedef  int u_int ;

/* Variables and functions */
 int ND_RA_FLAG_RTPREF_MASK ; 

__attribute__((used)) static const char *
get_rtpref(u_int v)
{
	static const char *rtpref_str[] = {
		"medium",		/* 00 */
		"high",			/* 01 */
		"rsv",			/* 10 */
		"low"			/* 11 */
	};

	return rtpref_str[((v & ND_RA_FLAG_RTPREF_MASK) >> 3) & 0xff];
}