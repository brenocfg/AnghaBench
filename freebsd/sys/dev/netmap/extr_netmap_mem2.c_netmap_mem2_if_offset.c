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
struct netmap_mem_d {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  netmap_if_offset (struct netmap_mem_d*,void const*) ; 

__attribute__((used)) static ssize_t
netmap_mem2_if_offset(struct netmap_mem_d *nmd, const void *addr)
{
	return netmap_if_offset(nmd, addr);
}