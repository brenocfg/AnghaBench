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
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  SND_DEV_STATUS ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  sndstat_cdevsw ; 
 int /*<<< orphan*/  sndstat_dev ; 
 int /*<<< orphan*/  sndstat_lock ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
sndstat_sysinit(void *p)
{
	sx_init(&sndstat_lock, "sndstat lock");
	sndstat_dev = make_dev(&sndstat_cdevsw, SND_DEV_STATUS,
	    UID_ROOT, GID_WHEEL, 0644, "sndstat");
}