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
struct TYPE_5__ {int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_6__ {int /*<<< orphan*/  zcr_free; int /*<<< orphan*/  zcr_finish; void* zcr_cbdata; int /*<<< orphan*/  zcr_cbinfo; } ;
typedef  TYPE_2__ zio_cksum_report_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_copy_to_buf (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* zio_buf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_buf_free ; 
 int /*<<< orphan*/  zio_vsd_default_cksum_finish ; 

void
zio_vsd_default_cksum_report(zio_t *zio, zio_cksum_report_t *zcr, void *ignored)
{
	void *buf = zio_buf_alloc(zio->io_size);

	abd_copy_to_buf(buf, zio->io_abd, zio->io_size);

	zcr->zcr_cbinfo = zio->io_size;
	zcr->zcr_cbdata = buf;
	zcr->zcr_finish = zio_vsd_default_cksum_finish;
	zcr->zcr_free = zio_buf_free;
}