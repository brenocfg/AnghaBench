#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct g_consumer {TYPE_1__* provider; TYPE_2__* geom; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  provider; } ;
struct TYPE_4__ {int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_LABEL_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SLICE_CONFIG_FORCE ; 
 TYPE_3__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_slice_config (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
g_label_resize(struct g_consumer *cp)
{

	G_LABEL_DEBUG(1, "Label %s resized.",
	    LIST_FIRST(&cp->geom->provider)->name);

	g_slice_config(cp->geom, 0, G_SLICE_CONFIG_FORCE, (off_t)0,
	    cp->provider->mediasize, cp->provider->sectorsize, "notused");
}