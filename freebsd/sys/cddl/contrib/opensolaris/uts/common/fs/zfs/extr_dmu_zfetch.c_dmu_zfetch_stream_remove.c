#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zs_lock; } ;
typedef  TYPE_1__ zstream_t ;
struct TYPE_8__ {int /*<<< orphan*/  zf_stream; int /*<<< orphan*/  zf_rwlock; } ;
typedef  TYPE_2__ zfetch_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmu_zfetch_stream_remove(zfetch_t *zf, zstream_t *zs)
{
	ASSERT(RW_WRITE_HELD(&zf->zf_rwlock));
	list_remove(&zf->zf_stream, zs);
	mutex_destroy(&zs->zs_lock);
	kmem_free(zs, sizeof (*zs));
}