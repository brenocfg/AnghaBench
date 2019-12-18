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
struct module {int dummy; } ;
typedef  int /*<<< orphan*/ * eventhandler_tag ;

/* Variables and functions */
 int EINVAL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  fuse_bringdown (int /*<<< orphan*/ *) ; 
 int fuse_device_init () ; 
 int /*<<< orphan*/  fuse_file_init () ; 
 int /*<<< orphan*/  fuse_internal_init () ; 
 int /*<<< orphan*/  fuse_ipc_init () ; 
 int /*<<< orphan*/  fuse_mtx ; 
 int /*<<< orphan*/  fuse_node_init () ; 
 int /*<<< orphan*/  fuse_pbuf_zone ; 
 int /*<<< orphan*/  fuse_vfsconf ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nswbuf ; 
 int /*<<< orphan*/  pbuf_zsecond_create (char*,int) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 
 int vfs_modevent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fuse_loader(struct module *m, int what, void *arg)
{
	static eventhandler_tag eh_tag = NULL;
	int err = 0;

	switch (what) {
	case MOD_LOAD:			/* kldload */
		mtx_init(&fuse_mtx, "fuse_mtx", NULL, MTX_DEF);
		err = fuse_device_init();
		if (err) {
			mtx_destroy(&fuse_mtx);
			return (err);
		}
		fuse_ipc_init();
		fuse_file_init();
		fuse_internal_init();
		fuse_node_init();
		fuse_pbuf_zone = pbuf_zsecond_create("fusepbuf", nswbuf / 2);

		/* vfs_modevent ignores its first arg */
		if ((err = vfs_modevent(NULL, what, &fuse_vfsconf)))
			fuse_bringdown(eh_tag);
		break;
	case MOD_UNLOAD:
		if ((err = vfs_modevent(NULL, what, &fuse_vfsconf)))
			return (err);
		fuse_bringdown(eh_tag);
		uma_zdestroy(fuse_pbuf_zone);
		break;
	default:
		return (EINVAL);
	}

	return (err);
}