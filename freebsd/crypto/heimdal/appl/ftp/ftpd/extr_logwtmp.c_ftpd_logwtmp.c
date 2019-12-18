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
 int /*<<< orphan*/  ftpd_logwtmp_asl (char*,char*,char*) ; 
 int /*<<< orphan*/  ftpd_logwtmp_wtmp (char*,char*,char*) ; 

void
ftpd_logwtmp(char *line, char *name, char *host)
{
#ifdef HAVE_ASL_H
    ftpd_logwtmp_asl(line, name, host);
#else
    ftpd_logwtmp_wtmp(line, name, host);
#endif
}