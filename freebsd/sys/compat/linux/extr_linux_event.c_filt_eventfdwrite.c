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
struct knote {struct eventfd* kn_hook; } ;
struct eventfd {int efd_count; int /*<<< orphan*/  efd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int UINT64_MAX ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_eventfdwrite(struct knote *kn, long hint)
{
	struct eventfd *efd = kn->kn_hook;
	int ret;

	mtx_assert(&efd->efd_lock, MA_OWNED);
	ret = (UINT64_MAX - 1 > efd->efd_count);

	return (ret);
}