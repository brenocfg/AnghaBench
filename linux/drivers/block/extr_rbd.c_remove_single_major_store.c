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
struct bus_type {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_rbd_remove (struct bus_type*,char const*,size_t) ; 

__attribute__((used)) static ssize_t remove_single_major_store(struct bus_type *bus, const char *buf,
					 size_t count)
{
	return do_rbd_remove(bus, buf, count);
}