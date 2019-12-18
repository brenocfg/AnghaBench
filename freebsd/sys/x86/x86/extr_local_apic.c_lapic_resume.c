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
struct pic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lapic_setup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lapic_resume(struct pic *pic, bool suspend_cancelled)
{

	lapic_setup(0);
}