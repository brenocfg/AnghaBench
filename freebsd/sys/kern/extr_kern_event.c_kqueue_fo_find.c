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
struct filterops {int dummy; } ;
struct TYPE_2__ {struct filterops* for_fop; int /*<<< orphan*/  for_refcnt; scalar_t__ for_nolock; } ;

/* Variables and functions */
 scalar_t__ EVFILT_SYSCOUNT ; 
 int /*<<< orphan*/  filterops_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct filterops null_filtops ; 
 TYPE_1__* sysfilt_ops ; 

__attribute__((used)) static struct filterops *
kqueue_fo_find(int filt)
{

	if (filt > 0 || filt + EVFILT_SYSCOUNT < 0)
		return NULL;

	if (sysfilt_ops[~filt].for_nolock)
		return sysfilt_ops[~filt].for_fop;

	mtx_lock(&filterops_lock);
	sysfilt_ops[~filt].for_refcnt++;
	if (sysfilt_ops[~filt].for_fop == NULL)
		sysfilt_ops[~filt].for_fop = &null_filtops;
	mtx_unlock(&filterops_lock);

	return sysfilt_ops[~filt].for_fop;
}