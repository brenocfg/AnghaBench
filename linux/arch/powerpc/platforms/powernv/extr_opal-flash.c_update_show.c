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
struct update_flash_t {int status; } ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct update_flash_t update_flash_data ; 

__attribute__((used)) static ssize_t update_show(struct kobject *kobj,
			   struct kobj_attribute *attr, char *buf)
{
	struct update_flash_t *const args_buf = &update_flash_data;
	return sprintf(buf, "%d\n", args_buf->status);
}