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

/* Variables and functions */
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uma_kmem_total ; 

__attribute__((used)) static inline void
uma_total_dec(unsigned long size)
{

	atomic_subtract_long(&uma_kmem_total, size);
}