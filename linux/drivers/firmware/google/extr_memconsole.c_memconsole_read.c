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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int /*<<< orphan*/  (* private ) (char*,int /*<<< orphan*/ ,size_t) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static ssize_t memconsole_read(struct file *filp, struct kobject *kobp,
			       struct bin_attribute *bin_attr, char *buf,
			       loff_t pos, size_t count)
{
	ssize_t (*memconsole_read_func)(char *, loff_t, size_t);

	memconsole_read_func = bin_attr->private;
	if (WARN_ON_ONCE(!memconsole_read_func))
		return -EIO;

	return memconsole_read_func(buf, pos, count);
}