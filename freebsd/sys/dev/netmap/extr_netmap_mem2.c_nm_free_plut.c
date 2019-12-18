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
struct plut_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (struct plut_entry*) ; 

__attribute__((used)) static void
nm_free_plut(struct plut_entry * lut)
{
	vfree(lut);
}