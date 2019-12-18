#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ldc_channel {int dummy; } ;
struct TYPE_4__ {int major; scalar_t__ minor; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  type; } ;
struct ds_ver_req {TYPE_2__ ver; TYPE_1__ tag; } ;
struct ds_msg_tag {int dummy; } ;
struct ds_info {int /*<<< orphan*/  hs_state; struct ldc_channel* lp; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DS_HS_START ; 
 int /*<<< orphan*/  DS_INIT_REQ ; 
 int __ds_send (struct ldc_channel*,struct ds_ver_req*,int) ; 

__attribute__((used)) static void ds_up(struct ds_info *dp)
{
	struct ldc_channel *lp = dp->lp;
	struct ds_ver_req req;
	int err;

	req.tag.type = DS_INIT_REQ;
	req.tag.len = sizeof(req) - sizeof(struct ds_msg_tag);
	req.ver.major = 1;
	req.ver.minor = 0;

	err = __ds_send(lp, &req, sizeof(req));
	if (err > 0)
		dp->hs_state = DS_HS_START;
}