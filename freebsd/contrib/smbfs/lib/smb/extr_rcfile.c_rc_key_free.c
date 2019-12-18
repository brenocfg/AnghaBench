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
struct rckey {struct rckey* rk_name; struct rckey* rk_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rckey*) ; 

__attribute__((used)) static void
rc_key_free(struct rckey *p)
{
	free(p->rk_value);
	free(p->rk_name);
	free(p);
}