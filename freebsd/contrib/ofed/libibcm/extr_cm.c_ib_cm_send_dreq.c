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
struct ib_cm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_USER_CM_CMD_SEND_DREQ ; 
 int cm_send_private_data (struct ib_cm_id*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int ib_cm_send_dreq(struct ib_cm_id *cm_id,
		    void *private_data,
		    uint8_t private_data_len)
{
	return cm_send_private_data(cm_id, IB_USER_CM_CMD_SEND_DREQ,
				    private_data, private_data_len);
}