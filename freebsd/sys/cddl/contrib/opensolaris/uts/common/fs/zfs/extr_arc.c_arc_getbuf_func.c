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
struct TYPE_5__ {scalar_t__ io_error; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_6__ {int /*<<< orphan*/ * b_data; } ;
typedef  TYPE_2__ arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

void
arc_getbuf_func(zio_t *zio, const zbookmark_phys_t *zb, const blkptr_t *bp,
    arc_buf_t *buf, void *arg)
{
	arc_buf_t **bufp = arg;
	if (buf == NULL) {
		ASSERT(zio == NULL || zio->io_error != 0);
		*bufp = NULL;
	} else {
		ASSERT(zio == NULL || zio->io_error == 0);
		*bufp = buf;
		ASSERT(buf->b_data != NULL);
	}
}