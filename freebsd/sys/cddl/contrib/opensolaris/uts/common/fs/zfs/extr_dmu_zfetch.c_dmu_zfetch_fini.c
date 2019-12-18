#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zstream_t ;
struct TYPE_4__ {int /*<<< orphan*/ * zf_dnode; int /*<<< orphan*/  zf_rwlock; int /*<<< orphan*/  zf_stream; } ;
typedef  TYPE_1__ zfetch_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  dmu_zfetch_stream_remove (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

void
dmu_zfetch_fini(zfetch_t *zf)
{
	zstream_t *zs;

	ASSERT(!RW_LOCK_HELD(&zf->zf_rwlock));

	rw_enter(&zf->zf_rwlock, RW_WRITER);
	while ((zs = list_head(&zf->zf_stream)) != NULL)
		dmu_zfetch_stream_remove(zf, zs);
	rw_exit(&zf->zf_rwlock);
	list_destroy(&zf->zf_stream);
	rw_destroy(&zf->zf_rwlock);

	zf->zf_dnode = NULL;
}