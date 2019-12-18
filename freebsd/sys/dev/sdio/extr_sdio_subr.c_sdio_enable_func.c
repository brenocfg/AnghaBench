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
struct sdio_func {int /*<<< orphan*/  fn; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_IO_CCCR_FN_ENABLE ; 
 int sdio_set_bool_for_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
sdio_enable_func(struct sdio_func *f)
{

	return (sdio_set_bool_for_func(f->dev, SD_IO_CCCR_FN_ENABLE,
	    f->fn, true));
}