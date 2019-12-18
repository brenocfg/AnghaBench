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
typedef  int uint32_t ;
struct TYPE_2__ {int pos; int size; int count; } ;
struct hid_item {scalar_t__ usage; int kind; int flags; scalar_t__ _usage_page; scalar_t__ usage_minimum; scalar_t__ usage_maximum; scalar_t__ set_delimiter; scalar_t__ string_maximum; scalar_t__ string_minimum; scalar_t__ string_index; scalar_t__ designator_maximum; scalar_t__ designator_minimum; scalar_t__ designator_index; TYPE_1__ loc; scalar_t__ unit; scalar_t__ unit_exponent; scalar_t__ physical_maximum; scalar_t__ physical_minimum; scalar_t__ logical_maximum; scalar_t__ logical_minimum; int /*<<< orphan*/  collevel; scalar_t__ collection; } ;
struct hid_data {size_t pushlevel; scalar_t__ icount; scalar_t__ ncount; size_t iusage; size_t nusage; scalar_t__* usages_min; scalar_t__ ousage; scalar_t__ usage_last; scalar_t__* usages_max; int kindset; int susage; scalar_t__ p; scalar_t__ end; int loc_count; int loc_size; struct hid_item* cur; } ;
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int HIO_VARIABLE ; 
 scalar_t__ MAXLOCCNT ; 
 size_t MAXPUSH ; 
 size_t MAXUSAGE ; 
 int /*<<< orphan*/  hid_clear_local (struct hid_item*) ; 
 int hid_collection ; 
 int hid_endcollection ; 
 int hid_feature ; 
 int hid_get_byte (struct hid_data*,unsigned int) ; 
 int hid_input ; 
 int hid_output ; 
 int /*<<< orphan*/  hid_switch_rid (struct hid_data*,struct hid_item*,scalar_t__) ; 

int
hid_get_item(struct hid_data *s, struct hid_item *h)
{
	struct hid_item *c;
	unsigned int bTag, bType, bSize;
	uint32_t oldpos;
	int32_t mask;
	int32_t dval;

	if (s == NULL)
		return (0);

	c = &s->cur[s->pushlevel];

 top:
	/* check if there is an array of items */
	if (s->icount < s->ncount) {
		/* get current usage */
		if (s->iusage < s->nusage) {
			dval = s->usages_min[s->iusage] + s->ousage;
			c->usage = dval;
			s->usage_last = dval;
			if (dval == s->usages_max[s->iusage]) {
				s->iusage ++;
				s->ousage = 0;
			} else {
				s->ousage ++;
			}
		} else {
			DPRINTFN(1, "Using last usage\n");
			dval = s->usage_last;
		}
		s->icount ++;
		/* 
		 * Only copy HID item, increment position and return
		 * if correct kindset!
		 */
		if (s->kindset & (1 << c->kind)) {
			*h = *c;
			DPRINTFN(1, "%u,%u,%u\n", h->loc.pos,
			    h->loc.size, h->loc.count);
			c->loc.pos += c->loc.size * c->loc.count;
			return (1);
		}
	}

	/* reset state variables */
	s->icount = 0;
	s->ncount = 0;
	s->iusage = 0;
	s->nusage = 0;
	s->susage = 0;
	s->ousage = 0;
	hid_clear_local(c);

	/* get next item */
	while (s->p != s->end) {

		bSize = hid_get_byte(s, 1);
		if (bSize == 0xfe) {
			/* long item */
			bSize = hid_get_byte(s, 1);
			bSize |= hid_get_byte(s, 1) << 8;
			bTag = hid_get_byte(s, 1);
			bType = 0xff;	/* XXX what should it be */
		} else {
			/* short item */
			bTag = bSize >> 4;
			bType = (bSize >> 2) & 3;
			bSize &= 3;
			if (bSize == 3)
				bSize = 4;
		}
		switch (bSize) {
		case 0:
			dval = 0;
			mask = 0;
			break;
		case 1:
			dval = (int8_t)hid_get_byte(s, 1);
			mask = 0xFF;
			break;
		case 2:
			dval = hid_get_byte(s, 1);
			dval |= hid_get_byte(s, 1) << 8;
			dval = (int16_t)dval;
			mask = 0xFFFF;
			break;
		case 4:
			dval = hid_get_byte(s, 1);
			dval |= hid_get_byte(s, 1) << 8;
			dval |= hid_get_byte(s, 1) << 16;
			dval |= hid_get_byte(s, 1) << 24;
			mask = 0xFFFFFFFF;
			break;
		default:
			dval = hid_get_byte(s, bSize);
			DPRINTFN(0, "bad length %u (data=0x%02x)\n",
			    bSize, dval);
			continue;
		}

		switch (bType) {
		case 0:		/* Main */
			switch (bTag) {
			case 8:	/* Input */
				c->kind = hid_input;
		ret:
				c->flags = dval;
				c->loc.count = s->loc_count;
				c->loc.size = s->loc_size;

				if (c->flags & HIO_VARIABLE) {
					/* range check usage count */
					if (c->loc.count > MAXLOCCNT) {
						DPRINTFN(0, "Number of "
						    "items(%u) truncated to %u\n",
						    (unsigned)(c->loc.count),
						    MAXLOCCNT);
						s->ncount = MAXLOCCNT;
					} else
						s->ncount = c->loc.count;

					/* 
					 * The "top" loop will return
					 * one and one item:
					 */
					c->loc.count = 1;
				} else {
					s->ncount = 1;
				}
				goto top;

			case 9:	/* Output */
				c->kind = hid_output;
				goto ret;
			case 10:	/* Collection */
				c->kind = hid_collection;
				c->collection = dval;
				c->collevel++;
				c->usage = s->usage_last;
				*h = *c;
				return (1);
			case 11:	/* Feature */
				c->kind = hid_feature;
				goto ret;
			case 12:	/* End collection */
				c->kind = hid_endcollection;
				if (c->collevel == 0) {
					DPRINTFN(0, "invalid end collection\n");
					return (0);
				}
				c->collevel--;
				*h = *c;
				return (1);
			default:
				DPRINTFN(0, "Main bTag=%d\n", bTag);
				break;
			}
			break;
		case 1:		/* Global */
			switch (bTag) {
			case 0:
				c->_usage_page = dval << 16;
				break;
			case 1:
				c->logical_minimum = dval;
				break;
			case 2:
				c->logical_maximum = dval;
				break;
			case 3:
				c->physical_minimum = dval;
				break;
			case 4:
				c->physical_maximum = dval;
				break;
			case 5:
				c->unit_exponent = dval;
				break;
			case 6:
				c->unit = dval;
				break;
			case 7:
				/* mask because value is unsigned */
				s->loc_size = dval & mask;
				break;
			case 8:
				hid_switch_rid(s, c, dval & mask);
				break;
			case 9:
				/* mask because value is unsigned */
				s->loc_count = dval & mask;
				break;
			case 10:	/* Push */
				s->pushlevel ++;
				if (s->pushlevel < MAXPUSH) {
					s->cur[s->pushlevel] = *c;
					/* store size and count */
					c->loc.size = s->loc_size;
					c->loc.count = s->loc_count;
					/* update current item pointer */
					c = &s->cur[s->pushlevel];
				} else {
					DPRINTFN(0, "Cannot push "
					    "item @ %d\n", s->pushlevel);
				}
				break;
			case 11:	/* Pop */
				s->pushlevel --;
				if (s->pushlevel < MAXPUSH) {
					/* preserve position */
					oldpos = c->loc.pos;
					c = &s->cur[s->pushlevel];
					/* restore size and count */
					s->loc_size = c->loc.size;
					s->loc_count = c->loc.count;
					/* set default item location */
					c->loc.pos = oldpos;
					c->loc.size = 0;
					c->loc.count = 0;
				} else {
					DPRINTFN(0, "Cannot pop "
					    "item @ %d\n", s->pushlevel);
				}
				break;
			default:
				DPRINTFN(0, "Global bTag=%d\n", bTag);
				break;
			}
			break;
		case 2:		/* Local */
			switch (bTag) {
			case 0:
				if (bSize != 4)
					dval = (dval & mask) | c->_usage_page;

				/* set last usage, in case of a collection */
				s->usage_last = dval;

				if (s->nusage < MAXUSAGE) {
					s->usages_min[s->nusage] = dval;
					s->usages_max[s->nusage] = dval;
					s->nusage ++;
				} else {
					DPRINTFN(0, "max usage reached\n");
				}

				/* clear any pending usage sets */
				s->susage = 0;
				break;
			case 1:
				s->susage |= 1;

				if (bSize != 4)
					dval = (dval & mask) | c->_usage_page;
				c->usage_minimum = dval;

				goto check_set;
			case 2:
				s->susage |= 2;

				if (bSize != 4)
					dval = (dval & mask) | c->_usage_page;
				c->usage_maximum = dval;

			check_set:
				if (s->susage != 3)
					break;

				/* sanity check */
				if ((s->nusage < MAXUSAGE) &&
				    (c->usage_minimum <= c->usage_maximum)) {
					/* add usage range */
					s->usages_min[s->nusage] = 
					    c->usage_minimum;
					s->usages_max[s->nusage] = 
					    c->usage_maximum;
					s->nusage ++;
				} else {
					DPRINTFN(0, "Usage set dropped\n");
				}
				s->susage = 0;
				break;
			case 3:
				c->designator_index = dval;
				break;
			case 4:
				c->designator_minimum = dval;
				break;
			case 5:
				c->designator_maximum = dval;
				break;
			case 7:
				c->string_index = dval;
				break;
			case 8:
				c->string_minimum = dval;
				break;
			case 9:
				c->string_maximum = dval;
				break;
			case 10:
				c->set_delimiter = dval;
				break;
			default:
				DPRINTFN(0, "Local bTag=%d\n", bTag);
				break;
			}
			break;
		default:
			DPRINTFN(0, "default bType=%d\n", bType);
			break;
		}
	}
	return (0);
}