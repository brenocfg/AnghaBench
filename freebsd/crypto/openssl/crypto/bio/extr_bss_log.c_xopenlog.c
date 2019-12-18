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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int LOG_CONS ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  openlog (char*,int,int) ; 

__attribute__((used)) static void xopenlog(BIO *bp, char *name, int level)
{
#  ifdef WATT32                 /* djgpp/DOS */
    openlog(name, LOG_PID | LOG_CONS | LOG_NDELAY, level);
#  else
    openlog(name, LOG_PID | LOG_CONS, level);
#  endif
}