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

/* Variables and functions */
 scalar_t__ MAXERRCODE ; 
 char const** auditd_errmsg ; 

const char *
auditd_strerror(int errcode)
{
	int idx = -errcode;

	if (idx < 0 || idx > (int)MAXERRCODE)
		return ("Invalid auditd error code");

	return (auditd_errmsg[idx]);
}