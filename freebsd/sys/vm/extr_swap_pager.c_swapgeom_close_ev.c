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
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_access (struct g_consumer*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 

__attribute__((used)) static void
swapgeom_close_ev(void *arg, int flags)
{
	struct g_consumer *cp;

	cp = arg;
	g_access(cp, -1, -1, 0);
	g_detach(cp);
	g_destroy_consumer(cp);
}