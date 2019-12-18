#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_consumer {TYPE_1__* geom; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_LABEL_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_slice_orphan (struct g_consumer*) ; 

__attribute__((used)) static void
g_label_orphan(struct g_consumer *cp)
{

	G_LABEL_DEBUG(1, "Label %s removed.",
	    LIST_FIRST(&cp->geom->provider)->name);
	g_slice_orphan(cp);
}