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
struct device_link {int /*<<< orphan*/  kref; int /*<<< orphan*/  status; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_FLAG_MANAGED ; 
 int /*<<< orphan*/  DL_STATE_NONE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __device_link_del ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_link_drop_managed(struct device_link *link)
{
	link->flags &= ~DL_FLAG_MANAGED;
	WRITE_ONCE(link->status, DL_STATE_NONE);
	kref_put(&link->kref, __device_link_del);
}