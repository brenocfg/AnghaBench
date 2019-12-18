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
typedef  int /*<<< orphan*/  pt2_entry_t ;

/* Variables and functions */
 int is_managed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte2_pa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline bool
pte2_is_managed(pt2_entry_t pte2)
{

	return (is_managed(pte2_pa(pte2)));
}