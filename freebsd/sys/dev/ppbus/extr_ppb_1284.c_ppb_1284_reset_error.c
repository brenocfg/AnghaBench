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
struct ppb_data {int state; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppb_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPB_NO_ERROR ; 

__attribute__((used)) static int
ppb_1284_reset_error(device_t bus, int state)
{
	struct ppb_data *ppb = DEVTOSOFTC(bus);

	ppb->error = PPB_NO_ERROR;
	ppb->state = state;

	return (0);
}