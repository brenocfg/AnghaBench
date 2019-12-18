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
typedef  int /*<<< orphan*/  n_time ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 

__attribute__((used)) static char *
pr_ntime(n_time timestamp)
{
	static char buf[11];
	int hour, min, sec;

	sec = ntohl(timestamp) / 1000;
	hour = sec / 60 / 60;
	min = (sec % (60 * 60)) / 60;
	sec = (sec % (60 * 60)) % 60;

	(void)snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hour, min, sec);

	return (buf);
}