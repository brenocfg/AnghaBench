#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; } ;
typedef  TYPE_2__ isc_entropysource_t ;
struct TYPE_10__ {int entropy; int pseudo; } ;
struct TYPE_12__ {int initialized; unsigned int nsources; int /*<<< orphan*/  sources; TYPE_2__* nextsource; TYPE_1__ pool; } ;
typedef  TYPE_3__ isc_entropy_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 scalar_t__ ENTROPY_SOURCETYPE_CALLBACK ; 
 scalar_t__ ENTROPY_SOURCETYPE_FILE ; 
 void* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_2__* ISC_LIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 unsigned int ISC_MAX (unsigned int,int) ; 
 unsigned int ISC_MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int RND_POOLBITS ; 
 int THRESHOLD_BITS ; 
 int VALID_ENTROPY (TYPE_3__*) ; 
 unsigned int get_from_callback (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int get_from_filesource (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
fillpool(isc_entropy_t *ent, unsigned int desired, isc_boolean_t blocking) {
	unsigned int added;
	unsigned int remaining;
	unsigned int needed;
	unsigned int nsource;
	isc_entropysource_t *source;
	isc_entropysource_t *firstsource;

	REQUIRE(VALID_ENTROPY(ent));

	needed = desired;

	/*
	 * This logic is a little strange, so an explanation is in order.
	 *
	 * If needed is 0, it means we are being asked to "fill to whatever
	 * we think is best."  This means that if we have at least a
	 * partially full pool (say, > 1/4th of the pool) we probably don't
	 * need to add anything.
	 *
	 * Also, we will check to see if the "pseudo" count is too high.
	 * If it is, try to mix in better data.  Too high is currently
	 * defined as 1/4th of the pool.
	 *
	 * Next, if we are asked to add a specific bit of entropy, make
	 * certain that we will do so.  Clamp how much we try to add to
	 * (DIGEST_SIZE * 8 < needed < POOLBITS - entropy).
	 *
	 * Note that if we are in a blocking mode, we will only try to
	 * get as much data as we need, not as much as we might want
	 * to build up.
	 */
	if (needed == 0) {
		REQUIRE(!blocking);

		if ((ent->pool.entropy >= RND_POOLBITS / 4)
		    && (ent->pool.pseudo <= RND_POOLBITS / 4))
			return;

		needed = THRESHOLD_BITS * 4;
	} else {
		needed = ISC_MAX(needed, THRESHOLD_BITS);
		needed = ISC_MIN(needed, RND_POOLBITS);
	}

	/*
	 * In any case, clamp how much we need to how much we can add.
	 */
	needed = ISC_MIN(needed, RND_POOLBITS - ent->pool.entropy);

	/*
	 * But wait!  If we're not yet initialized, we need at least
	 *	THRESHOLD_BITS
	 * of randomness.
	 */
	if (ent->initialized < THRESHOLD_BITS)
		needed = ISC_MAX(needed, THRESHOLD_BITS - ent->initialized);

	/*
	 * Poll each file source to see if we can read anything useful from
	 * it.  XXXMLG When where are multiple sources, we should keep a
	 * record of which one we last used so we can start from it (or the
	 * next one) to avoid letting some sources build up entropy while
	 * others are always drained.
	 */

	added = 0;
	remaining = needed;
	if (ent->nextsource == NULL) {
		ent->nextsource = ISC_LIST_HEAD(ent->sources);
		if (ent->nextsource == NULL)
			return;
	}
	source = ent->nextsource;
	/*
	 * Remember the first source so we can break if we have looped back to
	 * the beginning and still have nothing
	 */
	firstsource = source;
 again_file:
	for (nsource = 0; nsource < ent->nsources; nsource++) {
		unsigned int got;

		if (remaining == 0)
			break;

		got = 0;

		if (source->type == ENTROPY_SOURCETYPE_FILE)
			got = get_from_filesource(source, remaining);

		added += got;

		remaining -= ISC_MIN(remaining, got);

		source = ISC_LIST_NEXT(source, link);
		if (source == NULL)
			source = ISC_LIST_HEAD(ent->sources);
	}
	ent->nextsource = source;

	/*
	 * Go again only if there's been progress and we've not
	 * gone back to the beginning
	 */
	if (!(ent->nextsource == firstsource && added == 0)) {
		if (blocking && remaining != 0) {
				goto again_file;
		}
	}

	/*
	 * Here, if there are bits remaining to be had and we can block,
	 * check to see if we have a callback source.  If so, call them.
	 */
	source = ISC_LIST_HEAD(ent->sources);
	while ((remaining != 0) && (source != NULL)) {
		unsigned int got;

		got = 0;

		if (source->type == ENTROPY_SOURCETYPE_CALLBACK)
			got = get_from_callback(source, remaining, blocking);

		added += got;
		remaining -= ISC_MIN(remaining, got);

		if (added >= needed)
			break;

		source = ISC_LIST_NEXT(source, link);
	}

	/*
	 * Mark as initialized if we've added enough data.
	 */
	if (ent->initialized < THRESHOLD_BITS)
		ent->initialized += added;
}