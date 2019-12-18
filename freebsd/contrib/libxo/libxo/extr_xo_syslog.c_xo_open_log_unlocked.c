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
 int LOG_FACMASK ; 
 int LOG_NDELAY ; 
 int /*<<< orphan*/  xo_connect_log () ; 
 int xo_logfacility ; 
 int xo_logstat ; 
 char const* xo_logtag ; 
 int xo_opened ; 

__attribute__((used)) static void
xo_open_log_unlocked (const char *ident, int logstat, int logfac)
{
    if (ident != NULL)
        xo_logtag = ident;
    xo_logstat = logstat;
    if (logfac != 0 && (logfac &~ LOG_FACMASK) == 0)
        xo_logfacility = logfac;

    if (xo_logstat & LOG_NDELAY)    /* open immediately */
        xo_connect_log();

    xo_opened = 1;    /* ident and facility has been set */
}