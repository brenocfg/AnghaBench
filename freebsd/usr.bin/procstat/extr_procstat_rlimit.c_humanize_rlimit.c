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
typedef  scalar_t__ rlim_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  suffix; } ;

/* Variables and functions */
 int HN_AUTOSCALE ; 
 int /*<<< orphan*/  HN_DECIMAL ; 
 int HN_GETSCALE ; 
 scalar_t__ RLIM_INFINITY ; 
 int humanize_number (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* rlimit_param ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static const char *
humanize_rlimit(int indx, rlim_t limit)
{
	static char buf[14];
	int scale;

	if (limit == RLIM_INFINITY)
		return ("infinity     ");

	scale = humanize_number(buf, sizeof(buf) - 1, (int64_t)limit,
	    rlimit_param[indx].suffix, HN_AUTOSCALE | HN_GETSCALE, HN_DECIMAL);
	(void)humanize_number(buf, sizeof(buf) - 1, (int64_t)limit,
	    rlimit_param[indx].suffix, HN_AUTOSCALE, HN_DECIMAL);
	/* Pad with one space if there is no suffix prefix. */
	if (scale == 0)
		sprintf(buf + strlen(buf), " ");
	return (buf);
}