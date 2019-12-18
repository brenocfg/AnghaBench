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
struct packing_data {unsigned long* delta_size; struct object_entry const* objects; } ;
struct object_entry {unsigned long delta_size_; scalar_t__ delta_size_valid; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long oe_delta_size(struct packing_data *pack,
					  const struct object_entry *e)
{
	if (e->delta_size_valid)
		return e->delta_size_;

	/*
	 * pack->delta_size[] can't be NULL because oe_set_delta_size()
	 * must have been called when a new delta is saved with
	 * oe_set_delta().
	 * If oe_delta() returns NULL (i.e. default state, which means
	 * delta_size_valid is also false), then the caller must never
	 * call oe_delta_size().
	 */
	return pack->delta_size[e - pack->objects];
}