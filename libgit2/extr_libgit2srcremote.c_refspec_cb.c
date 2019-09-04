#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct refspec_cb_data {int /*<<< orphan*/  fetch; int /*<<< orphan*/  remote; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;

/* Variables and functions */
 int add_refspec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int refspec_cb(const git_config_entry *entry, void *payload)
{
	struct refspec_cb_data *data = (struct refspec_cb_data *)payload;
	return add_refspec(data->remote, entry->value, data->fetch);
}