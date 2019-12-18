#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbuf {int dummy; } ;
struct g_provider {int dummy; } ;
struct g_geom {int dummy; } ;
struct g_consumer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queues; int /*<<< orphan*/  units; } ;

/* Variables and functions */
 TYPE_1__ me ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_rr_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp,
    struct g_consumer *cp, struct g_provider *pp)
{
	if (indent == NULL) {   /* plaintext */
		sbuf_printf(sb, " units %d queues %d",
			me.units, me.queues);
        }
}