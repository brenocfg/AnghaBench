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
struct device_connection {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  devcon_list ; 
 int /*<<< orphan*/  devcon_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void device_connection_add(struct device_connection *con)
{
	mutex_lock(&devcon_lock);
	list_add_tail(&con->list, &devcon_list);
	mutex_unlock(&devcon_lock);
}