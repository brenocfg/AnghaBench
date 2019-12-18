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
struct coh901318_lli {scalar_t__ link_addr; scalar_t__ virt_link_addr; } ;

/* Variables and functions */

__attribute__((used)) static struct coh901318_lli *
coh901318_lli_next(struct coh901318_lli *data)
{
	if (data == NULL || data->link_addr == 0)
		return NULL;

	return (struct coh901318_lli *) data->virt_link_addr;
}