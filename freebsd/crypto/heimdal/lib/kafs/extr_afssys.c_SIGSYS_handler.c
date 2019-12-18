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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSYS ; 
 int /*<<< orphan*/  catch_SIGSYS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int)) ; 

__attribute__((used)) static RETSIGTYPE
SIGSYS_handler(int sig)
{
    errno = 0;
    signal(SIGSYS, SIGSYS_handler); /* Need to reinstall handler on SYSV */
    longjmp(catch_SIGSYS, 1);
}