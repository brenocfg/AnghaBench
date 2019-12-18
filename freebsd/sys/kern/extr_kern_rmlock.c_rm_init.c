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
struct rmlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rm_init_flags (struct rmlock*,char const*,int /*<<< orphan*/ ) ; 

void
rm_init(struct rmlock *rm, const char *name)
{

	rm_init_flags(rm, name, 0);
}