#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char isc_uint8_t ;
typedef  int isc_uint32_t ;
typedef  int /*<<< orphan*/  isc_sha1_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_11__ {unsigned int entropy; scalar_t__ pool; } ;
struct TYPE_12__ {unsigned int initialized; int /*<<< orphan*/  lock; TYPE_1__ pool; } ;
typedef  TYPE_2__ isc_entropy_t ;
typedef  scalar_t__ isc_boolean_t ;
typedef  int /*<<< orphan*/  digest ;

/* Variables and functions */
 unsigned int ISC_ENTROPY_BLOCKING ; 
 unsigned int ISC_ENTROPY_GOODONLY ; 
 unsigned int ISC_ENTROPY_PARTIAL ; 
 scalar_t__ ISC_FALSE ; 
 unsigned int ISC_MAX (int,int) ; 
 int ISC_MIN (int,unsigned int) ; 
 int /*<<< orphan*/  ISC_R_NOENTROPY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int ISC_SHA1_DIGESTLENGTH ; 
 scalar_t__ ISC_TF (int) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 unsigned int RND_ENTROPY_THRESHOLD ; 
 int /*<<< orphan*/  RND_POOLBYTES ; 
 unsigned int THRESHOLD_BITS ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_ENTROPY (TYPE_2__*) ; 
 int /*<<< orphan*/  add_entropy (TYPE_2__*,int) ; 
 int /*<<< orphan*/  add_pseudo (TYPE_2__*,int) ; 
 int /*<<< orphan*/  entropypool_adddata (TYPE_2__*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillpool (TYPE_2__*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  isc_sha1_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  isc_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_sha1_update (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reseed (TYPE_2__*) ; 
 int /*<<< orphan*/  subtract_entropy (TYPE_2__*,int) ; 

isc_result_t
isc_entropy_getdata(isc_entropy_t *ent, void *data, unsigned int length,
		    unsigned int *returned, unsigned int flags)
{
	unsigned int i;
	isc_sha1_t hash;
	unsigned char digest[ISC_SHA1_DIGESTLENGTH];
	isc_uint32_t remain, deltae, count, total;
	isc_uint8_t *buf;
	isc_boolean_t goodonly, partial, blocking;

	REQUIRE(VALID_ENTROPY(ent));
	REQUIRE(data != NULL);
	REQUIRE(length > 0);

	goodonly = ISC_TF((flags & ISC_ENTROPY_GOODONLY) != 0);
	partial = ISC_TF((flags & ISC_ENTROPY_PARTIAL) != 0);
	blocking = ISC_TF((flags & ISC_ENTROPY_BLOCKING) != 0);

	REQUIRE(!partial || returned != NULL);

	LOCK(&ent->lock);

	remain = length;
	buf = data;
	total = 0;
	while (remain != 0) {
		count = ISC_MIN(remain, RND_ENTROPY_THRESHOLD);

		/*
		 * If we are extracting good data only, make certain we
		 * have enough data in our pool for this pass.  If we don't,
		 * get some, and fail if we can't, and partial returns
		 * are not ok.
		 */
		if (goodonly) {
			unsigned int fillcount;

			fillcount = ISC_MAX(remain * 8, count * 8);

			/*
			 * If, however, we have at least THRESHOLD_BITS
			 * of entropy in the pool, don't block here.  It is
			 * better to drain the pool once in a while and
			 * then refill it than it is to constantly keep the
			 * pool full.
			 */
			if (ent->pool.entropy >= THRESHOLD_BITS)
				fillpool(ent, fillcount, ISC_FALSE);
			else
				fillpool(ent, fillcount, blocking);

			/*
			 * Verify that we got enough entropy to do one
			 * extraction.  If we didn't, bail.
			 */
			if (ent->pool.entropy < THRESHOLD_BITS) {
				if (!partial)
					goto zeroize;
				else
					goto partial_output;
			}
		} else {
			/*
			 * If we've extracted half our pool size in bits
			 * since the last refresh, try to refresh here.
			 */
			if (ent->initialized < THRESHOLD_BITS)
				fillpool(ent, THRESHOLD_BITS, blocking);
			else
				fillpool(ent, 0, ISC_FALSE);

			/*
			 * If we've not initialized with enough good random
			 * data, seed with our crappy code.
			 */
			if (ent->initialized < THRESHOLD_BITS)
				reseed(ent);
		}

		isc_sha1_init(&hash);
		isc_sha1_update(&hash, (void *)(ent->pool.pool),
				RND_POOLBYTES);
		isc_sha1_final(&hash, digest);

		/*
		 * Stir the extracted data (all of it) back into the pool.
		 */
		entropypool_adddata(ent, digest, ISC_SHA1_DIGESTLENGTH, 0);

		for (i = 0; i < count; i++)
			buf[i] = digest[i] ^ digest[i + RND_ENTROPY_THRESHOLD];

		buf += count;
		remain -= count;

		deltae = count * 8;
		deltae = ISC_MIN(deltae, ent->pool.entropy);
		total += deltae;
		subtract_entropy(ent, deltae);
		add_pseudo(ent, count * 8);
	}

 partial_output:
	memset(digest, 0, sizeof(digest));

	if (returned != NULL)
		*returned = (length - remain);

	UNLOCK(&ent->lock);

	return (ISC_R_SUCCESS);

 zeroize:
	/* put the entropy we almost extracted back */
	add_entropy(ent, total);
	memset(data, 0, length);
	memset(digest, 0, sizeof(digest));
	if (returned != NULL)
		*returned = 0;

	UNLOCK(&ent->lock);

	return (ISC_R_NOENTROPY);
}