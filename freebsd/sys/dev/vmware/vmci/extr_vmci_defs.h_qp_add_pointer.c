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
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t qp_atomic_read_offset (size_t volatile*) ; 
 int /*<<< orphan*/  qp_atomic_write_offset (size_t volatile*,size_t) ; 

__attribute__((used)) static inline void
qp_add_pointer(volatile uint64_t *var, size_t add, uint64_t size)
{
	uint64_t new_val = qp_atomic_read_offset(var);

	if (new_val >= size - add)
		new_val -= size;

	new_val += add;
	qp_atomic_write_offset(var, new_val);
}