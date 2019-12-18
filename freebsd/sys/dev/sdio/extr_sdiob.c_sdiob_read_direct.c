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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int sdio_rw_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sdiob_read_direct(device_t dev, uint8_t fn, uint32_t addr, uint8_t *val)
{
	int error;
	uint8_t v;

	error = sdio_rw_direct(dev, fn, addr, false, &v);
	/* Be polite and do not touch the value on read error. */
	if (error == 0 && val != NULL)
		*val = v;
	return (error);
}