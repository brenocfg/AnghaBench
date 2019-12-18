#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t wchar_t ;
struct xlocale_collate {TYPE_3__* info; TYPE_1__* char_pri_table; } ;
struct TYPE_9__ {int* pri; } ;
struct TYPE_11__ {TYPE_2__ pri; } ;
typedef  TYPE_4__ collate_large_t ;
struct TYPE_12__ {int* pri; } ;
typedef  TYPE_5__ collate_chain_t ;
struct TYPE_10__ {int directive_count; scalar_t__ large_count; int* directive; int* undef_pri; } ;
struct TYPE_8__ {int* pri; } ;

/* Variables and functions */
 size_t const COLLATE_MAX_PRIORITY ; 
 int DIRECTIVE_UNDEFINED ; 
 size_t const UCHAR_MAX ; 
 TYPE_5__* chainsearch (struct xlocale_collate*,size_t const*,int*) ; 
 TYPE_4__* largesearch (struct xlocale_collate*,size_t const) ; 
 int* substsearch (struct xlocale_collate*,int,int) ; 

void
_collate_lookup(struct xlocale_collate *table, const wchar_t *t, int *len,
    int *pri, int which, const int **state)
{
	collate_chain_t *p2;
	collate_large_t *match;
	int p, l;
	const int *sptr;

	/*
	 * If this is the "last" pass for the UNDEFINED, then
	 * we just return the priority itself.
	 */
	if (which >= table->info->directive_count) {
		*pri = *t;
		*len = 1;
		*state = NULL;
		return;
	}

	/*
	 * If we have remaining substitution data from a previous
	 * call, consume it first.
	 */
	if ((sptr = *state) != NULL) {
		*pri = *sptr;
		sptr++;
		if ((sptr == *state) || (sptr == NULL))
			*state = NULL;
		else
			*state = sptr;
		*len = 0;
		return;
	}

	/* No active substitutions */
	*len = 1;

	/*
	 * Check for composites such as diphthongs that collate as a
	 * single element (aka chains or collating-elements).
	 */
	if (((p2 = chainsearch(table, t, &l)) != NULL) &&
	    ((p = p2->pri[which]) >= 0)) {

		*len = l;
		*pri = p;

	} else if (*t <= UCHAR_MAX) {

		/*
		 * Character is a small (8-bit) character.
		 * We just look these up directly for speed.
		 */
		*pri = table->char_pri_table[*t].pri[which];

	} else if ((table->info->large_count > 0) &&
	    ((match = largesearch(table, *t)) != NULL)) {

		/*
		 * Character was found in the extended table.
		 */
		*pri = match->pri.pri[which];

	} else {
		/*
		 * Character lacks a specific definition.
		 */
		if (table->info->directive[which] & DIRECTIVE_UNDEFINED) {
			/* Mask off sign bit to prevent ordering confusion. */
			*pri = (*t & COLLATE_MAX_PRIORITY);
		} else {
			*pri = table->info->undef_pri[which];
		}
		/* No substitutions for undefined characters! */
		return;
	}

	/*
	 * Try substituting (expanding) the character.  We are
	 * currently doing this *after* the chain compression.  I
	 * think it should not matter, but this way might be slightly
	 * faster.
	 *
	 * We do this after the priority search, as this will help us
	 * to identify a single key value.  In order for this to work,
	 * its important that the priority assigned to a given element
	 * to be substituted be unique for that level.  The localedef
	 * code ensures this for us.
	 */
	if ((sptr = substsearch(table, *pri, which)) != NULL) {
		if ((*pri = *sptr) > 0) {
			sptr++;
			*state = *sptr ? sptr : NULL;
		}
	}

}