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
struct ssif_info {int /*<<< orphan*/  intf; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct ssif_info* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  ipmi_unregister_smi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ssif_info*) ; 

__attribute__((used)) static void ssif_remove_dup(struct i2c_client *client)
{
	struct ssif_info *ssif_info = i2c_get_clientdata(client);

	ipmi_unregister_smi(ssif_info->intf);
	kfree(ssif_info);
}