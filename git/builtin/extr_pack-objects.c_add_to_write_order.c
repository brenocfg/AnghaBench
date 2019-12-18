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
struct object_entry {int filled; } ;

/* Variables and functions */
 scalar_t__ oe_layer (int /*<<< orphan*/ *,struct object_entry*) ; 
 int /*<<< orphan*/  to_pack ; 
 scalar_t__ write_layer ; 

__attribute__((used)) static inline void add_to_write_order(struct object_entry **wo,
			       unsigned int *endp,
			       struct object_entry *e)
{
	if (e->filled || oe_layer(&to_pack, e) != write_layer)
		return;
	wo[(*endp)++] = e;
	e->filled = 1;
}