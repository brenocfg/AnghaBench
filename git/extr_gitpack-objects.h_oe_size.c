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
struct packing_data {int dummy; } ;
struct object_entry {unsigned long size_; scalar_t__ size_valid; } ;

/* Variables and functions */
 unsigned long oe_get_size_slow (struct packing_data*,struct object_entry const*) ; 

__attribute__((used)) static inline unsigned long oe_size(struct packing_data *pack,
				    const struct object_entry *e)
{
	if (e->size_valid)
		return e->size_;

	return oe_get_size_slow(pack, e);
}