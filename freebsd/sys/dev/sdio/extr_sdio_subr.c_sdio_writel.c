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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sdio_func {int /*<<< orphan*/  fn; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SDIO_WRITE_EXTENDED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

void
sdio_writel(struct sdio_func *f, uint32_t val, uint32_t addr, int *err)
{
	int error;

	error = SDIO_WRITE_EXTENDED(device_get_parent(f->dev), f->fn, addr,
	    sizeof(val), (uint8_t *)&val, false);
	if (err != NULL)
		*err = error;
}