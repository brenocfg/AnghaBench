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
struct ipmi_smi_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  smi_msg_inuse_count ; 

__attribute__((used)) static void free_smi_msg(struct ipmi_smi_msg *msg)
{
	atomic_dec(&smi_msg_inuse_count);
	kfree(msg);
}