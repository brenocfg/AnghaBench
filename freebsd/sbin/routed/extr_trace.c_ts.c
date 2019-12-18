#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cftime (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ctime (int /*<<< orphan*/ *) ; 
 TYPE_1__ epoch ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 

__attribute__((used)) static char *
ts(time_t secs) {
	static char s[20];

	secs += epoch.tv_sec;
#ifdef sgi
	(void)cftime(s, "%T", &secs);
#else
	memcpy(s, ctime(&secs)+11, 8);
	s[8] = '\0';
#endif
	return s;
}