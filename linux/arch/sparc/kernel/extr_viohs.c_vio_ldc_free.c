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
struct vio_driver_state {scalar_t__ desc_buf_len; int /*<<< orphan*/ * desc_buf; int /*<<< orphan*/ * lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldc_free (int /*<<< orphan*/ *) ; 

void vio_ldc_free(struct vio_driver_state *vio)
{
	ldc_free(vio->lp);
	vio->lp = NULL;

	kfree(vio->desc_buf);
	vio->desc_buf = NULL;
	vio->desc_buf_len = 0;
}