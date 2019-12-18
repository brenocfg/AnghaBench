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
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ID_REMOVE ; 
 int /*<<< orphan*/  do_id_store (struct device_driver*,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t remove_id_store(struct device_driver *drv, const char *buf,
		size_t count)
{
	return do_id_store(drv, buf, count, ID_REMOVE);
}