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
struct vmbus_gpa {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct hn_nvs_sendctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_NVS_RNDIS_MTYPE_CTRL ; 
 int hn_nvs_send_rndis_sglist (struct vmbus_channel*,int /*<<< orphan*/ ,struct hn_nvs_sendctx*,struct vmbus_gpa*,int) ; 

int
hn_nvs_send_rndis_ctrl(struct vmbus_channel *chan,
    struct hn_nvs_sendctx *sndc, struct vmbus_gpa *gpa, int gpa_cnt)
{

	return hn_nvs_send_rndis_sglist(chan, HN_NVS_RNDIS_MTYPE_CTRL,
	    sndc, gpa, gpa_cnt);
}