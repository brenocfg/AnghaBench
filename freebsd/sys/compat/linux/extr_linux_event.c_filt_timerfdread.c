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
struct timerfd {scalar_t__ tfd_count; } ;
struct knote {struct timerfd* kn_hook; } ;

/* Variables and functions */

__attribute__((used)) static int
filt_timerfdread(struct knote *kn, long hint)
{
	struct timerfd *tfd = kn->kn_hook;

	return (tfd->tfd_count > 0);
}