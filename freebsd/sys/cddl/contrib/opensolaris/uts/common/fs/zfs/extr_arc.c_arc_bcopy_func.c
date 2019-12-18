#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_data; } ;
typedef  TYPE_1__ arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  arc_buf_destroy (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  arc_buf_size (TYPE_1__*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void
arc_bcopy_func(zio_t *zio, const zbookmark_phys_t *zb, const blkptr_t *bp,
    arc_buf_t *buf, void *arg)
{
	if (buf == NULL)
		return;

	bcopy(buf->b_data, arg, arc_buf_size(buf));
	arc_buf_destroy(buf, arg);
}