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
struct g_virstor_softc {int dummy; } ;
struct bio {scalar_t__ bio_error; scalar_t__ bio_inbed; scalar_t__ bio_children; scalar_t__ bio_length; scalar_t__ bio_completed; TYPE_2__* bio_to; int /*<<< orphan*/  bio_offset; struct bio* bio_parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_virstor_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_MSG (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVL_ERROR ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,scalar_t__) ; 

__attribute__((used)) static void
g_virstor_done(struct bio *b)
{
	struct g_virstor_softc *sc;
	struct bio *parent_b;

	parent_b = b->bio_parent;
	sc = parent_b->bio_to->geom->softc;

	if (b->bio_error != 0) {
		LOG_MSG(LVL_ERROR, "Error %d for offset=%ju, length=%ju, %s",
		    b->bio_error, b->bio_offset, b->bio_length,
		    b->bio_to->name);
		if (parent_b->bio_error == 0)
			parent_b->bio_error = b->bio_error;
	}

	parent_b->bio_inbed++;
	parent_b->bio_completed += b->bio_completed;

	if (parent_b->bio_children == parent_b->bio_inbed) {
		parent_b->bio_completed = parent_b->bio_length;
		g_io_deliver(parent_b, parent_b->bio_error);
	}
	g_destroy_bio(b);
}