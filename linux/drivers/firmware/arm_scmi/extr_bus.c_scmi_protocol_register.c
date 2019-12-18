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
typedef  int /*<<< orphan*/  scmi_prot_init_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  protocol_lock ; 
 int /*<<< orphan*/  scmi_protocols ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int scmi_protocol_register(int protocol_id, scmi_prot_init_fn_t fn)
{
	int ret;

	spin_lock(&protocol_lock);
	ret = idr_alloc(&scmi_protocols, fn, protocol_id, protocol_id + 1,
			GFP_ATOMIC);
	spin_unlock(&protocol_lock);
	if (ret != protocol_id)
		pr_err("unable to allocate SCMI idr slot, err %d\n", ret);

	return ret;
}