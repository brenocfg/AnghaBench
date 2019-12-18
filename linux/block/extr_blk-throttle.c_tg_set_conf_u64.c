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
struct kernfs_open_file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  tg_set_conf (struct kernfs_open_file*,char*,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t tg_set_conf_u64(struct kernfs_open_file *of,
			       char *buf, size_t nbytes, loff_t off)
{
	return tg_set_conf(of, buf, nbytes, off, true);
}