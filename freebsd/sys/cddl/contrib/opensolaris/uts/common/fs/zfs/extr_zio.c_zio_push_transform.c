#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* zt_next; int /*<<< orphan*/ * zt_transform; void* zt_bufsize; void* zt_orig_size; int /*<<< orphan*/ * zt_orig_abd; } ;
typedef  TYPE_1__ zio_transform_t ;
typedef  int /*<<< orphan*/  zio_transform_func_t ;
struct TYPE_6__ {void* io_size; int /*<<< orphan*/ * io_abd; TYPE_1__* io_transform_stack; } ;
typedef  TYPE_2__ zio_t ;
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMPLY (int,int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int abd_is_linear (int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 

void
zio_push_transform(zio_t *zio, abd_t *data, uint64_t size, uint64_t bufsize,
    zio_transform_func_t *transform)
{
	zio_transform_t *zt = kmem_alloc(sizeof (zio_transform_t), KM_SLEEP);

	/*
	 * Ensure that anyone expecting this zio to contain a linear ABD isn't
	 * going to get a nasty surprise when they try to access the data.
	 */
#ifdef illumos
	IMPLY(abd_is_linear(zio->io_abd), abd_is_linear(data));
#else
	IMPLY(zio->io_abd != NULL && abd_is_linear(zio->io_abd),
	    abd_is_linear(data));
#endif

	zt->zt_orig_abd = zio->io_abd;
	zt->zt_orig_size = zio->io_size;
	zt->zt_bufsize = bufsize;
	zt->zt_transform = transform;

	zt->zt_next = zio->io_transform_stack;
	zio->io_transform_stack = zt;

	zio->io_abd = data;
	zio->io_size = size;
}