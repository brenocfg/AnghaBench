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
struct g_geom {int /*<<< orphan*/  consumer; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_NOP_LOGREQ (struct bio*,char*) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_nop_pass(struct bio *cbp, struct g_geom *gp)
{

	G_NOP_LOGREQ(cbp, "Sending request.");
	g_io_request(cbp, LIST_FIRST(&gp->consumer));
}