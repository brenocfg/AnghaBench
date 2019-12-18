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
typedef  size_t uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  pos; } ;
struct hid_item {scalar_t__ report_ID; TYPE_2__ loc; } ;
struct hid_data {TYPE_1__* last_pos; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__ rid; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 size_t MAXID ; 

__attribute__((used)) static void
hid_switch_rid(struct hid_data *s, struct hid_item *c, int32_t next_rID)
{
	uint8_t i;

	/* check for same report ID - optimise */

	if (c->report_ID == next_rID)
		return;

	/* save current position for current rID */

	if (c->report_ID == 0) {
		i = 0;
	} else {
		for (i = 1; i != MAXID; i++) {
			if (s->last_pos[i].rid == c->report_ID)
				break;
			if (s->last_pos[i].rid == 0)
				break;
		}
	}
	if (i != MAXID) {
		s->last_pos[i].rid = c->report_ID;
		s->last_pos[i].pos = c->loc.pos;
	}

	/* store next report ID */

	c->report_ID = next_rID;

	/* lookup last position for next rID */

	if (next_rID == 0) {
		i = 0;
	} else {
		for (i = 1; i != MAXID; i++) {
			if (s->last_pos[i].rid == next_rID)
				break;
			if (s->last_pos[i].rid == 0)
				break;
		}
	}
	if (i != MAXID) {
		s->last_pos[i].rid = next_rID;
		c->loc.pos = s->last_pos[i].pos;
	} else {
		DPRINTF("Out of RID entries, position is set to zero!\n");
		c->loc.pos = 0;
	}
}