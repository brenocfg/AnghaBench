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
typedef  int /*<<< orphan*/  u_int32_t ;
struct cam_devq {int /*<<< orphan*/  send_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  camq_resize (int /*<<< orphan*/ *,int) ; 

u_int32_t
cam_devq_resize(struct cam_devq *camq, int devices)
{
	u_int32_t retval;

	retval = camq_resize(&camq->send_queue, devices);
	return (retval);
}