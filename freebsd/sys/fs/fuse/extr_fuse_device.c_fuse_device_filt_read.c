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
struct knote {int kn_data; int /*<<< orphan*/  kn_fflags; int /*<<< orphan*/  kn_flags; scalar_t__ kn_hook; } ;
struct fuse_data {int ms_count; int /*<<< orphan*/  ms_head; int /*<<< orphan*/  ms_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EV_EOF ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ fdata_get_dead (struct fuse_data*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fuse_device_filt_read(struct knote *kn, long hint)
{
	struct fuse_data *data;
	int ready;

	data = (struct fuse_data*)kn->kn_hook;
	MPASS(data != NULL);

	mtx_assert(&data->ms_mtx, MA_OWNED);
	if (fdata_get_dead(data)) {
		kn->kn_flags |= EV_EOF;
		kn->kn_fflags = ENODEV;
		kn->kn_data = 1;
		ready = 1;
	} else if (STAILQ_FIRST(&data->ms_head)) {
		MPASS(data->ms_count >= 1);
		kn->kn_data = data->ms_count;
		ready = 1;
	} else {
		ready = 0;
	}

	return (ready);
}