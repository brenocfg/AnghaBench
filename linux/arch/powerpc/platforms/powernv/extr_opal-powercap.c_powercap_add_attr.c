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
struct TYPE_4__ {char const* name; int mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  show; TYPE_2__ attr; } ;
struct powercap_attr {int handle; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  powercap_show ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static void powercap_add_attr(int handle, const char *name,
			      struct powercap_attr *attr)
{
	attr->handle = handle;
	sysfs_attr_init(&attr->attr.attr);
	attr->attr.attr.name = name;
	attr->attr.attr.mode = 0444;
	attr->attr.show = powercap_show;
}