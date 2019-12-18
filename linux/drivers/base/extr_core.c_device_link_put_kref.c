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
struct device_link {int flags; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int DL_FLAG_STATELESS ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  __device_link_del ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_link_put_kref(struct device_link *link)
{
	if (link->flags & DL_FLAG_STATELESS)
		kref_put(&link->kref, __device_link_del);
	else
		WARN(1, "Unable to drop a managed device link reference\n");
}