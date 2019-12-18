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
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ alarmed ; 
 int /*<<< orphan*/  set_tty_parameters () ; 
 int /*<<< orphan*/  sigalrm ; 
 int /*<<< orphan*/  sighup ; 
 int /*<<< orphan*/  sigint ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm ; 

void init(void)
{
    signal(SIGINT, sigint);
    signal(SIGTERM, sigterm);
    signal(SIGHUP, sighup);

    set_tty_parameters();
    signal(SIGALRM, sigalrm);
    alarm(0);
    alarmed = 0;
}