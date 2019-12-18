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
typedef  size_t uint8_t ;
struct hid_item {scalar_t__ report_ID; } ;
struct hid_data {scalar_t__* pos; TYPE_1__* last_pos; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ rid; scalar_t__* pos; } ;

/* Variables and functions */
 size_t ITEMTYPES ; 
 size_t MAXID ; 

__attribute__((used)) static void
hid_switch_rid(struct hid_data *s, struct hid_item *c, int32_t next_rID)
{
	uint8_t i, j;

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
		for (j = 0; j < ITEMTYPES; j++)
			s->last_pos[i].pos[j] = s->pos[j];
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
		for (j = 0; j < ITEMTYPES; j++)
			s->pos[j] = s->last_pos[i].pos[j];
	} else {
		for (j = 0; j < ITEMTYPES; j++)
			s->pos[j] = 0;	/* Out of RID entries. */
	}
}