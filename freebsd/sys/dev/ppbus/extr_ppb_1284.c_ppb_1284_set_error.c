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
struct ppb_data {int error; scalar_t__ state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppb_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 scalar_t__ PPB_ERROR ; 
 int PPB_NO_ERROR ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static int
ppb_1284_set_error(device_t bus, int error, int event)
{
	struct ppb_data *ppb = DEVTOSOFTC(bus);

	/* do not accumulate errors */
	if ((ppb->error == PPB_NO_ERROR) &&
			(ppb->state != PPB_ERROR)) {
		ppb->error = error;
		ppb->state = PPB_ERROR;
	}

#ifdef DEBUG_1284
	printf("ppb1284: error=%d status=0x%x event=%d\n", error,
		ppb_rstr(bus) & 0xff, event);
#endif

	return (0);
}