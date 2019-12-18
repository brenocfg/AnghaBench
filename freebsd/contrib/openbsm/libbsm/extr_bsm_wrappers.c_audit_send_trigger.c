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

/* Variables and functions */
 int /*<<< orphan*/  A_SENDTRIGGER ; 
 int auditon (int /*<<< orphan*/ ,int*,int) ; 

int
audit_send_trigger(int *trigger)
{

	return (auditon(A_SENDTRIGGER, trigger, sizeof(*trigger)));
}