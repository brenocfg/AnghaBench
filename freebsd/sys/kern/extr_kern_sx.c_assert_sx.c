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
struct sx {int dummy; } ;
struct lock_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_assert (struct sx const*,int) ; 

void
assert_sx(const struct lock_object *lock, int what)
{

	sx_assert((const struct sx *)lock, what);
}