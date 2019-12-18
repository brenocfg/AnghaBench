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
typedef  int uint64_t ;
typedef  int time_t ;

/* Variables and functions */
 int EPOC_TIME ; 

__attribute__((used)) static time_t
lha_win_time(uint64_t wintime, long *ns)
{
#define EPOC_TIME ARCHIVE_LITERAL_ULL(116444736000000000)

	if (wintime >= EPOC_TIME) {
		wintime -= EPOC_TIME;	/* 1970-01-01 00:00:00 (UTC) */
		if (ns != NULL)
			*ns = (long)(wintime % 10000000) * 100;
		return (wintime / 10000000);
	} else {
		if (ns != NULL)
			*ns = 0;
		return (0);
	}
}