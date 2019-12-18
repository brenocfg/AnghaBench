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
struct repository {TYPE_1__* hash_algo; } ;
struct object_id {int dummy; } ;
struct min_abbrev_data {int init_len; int cur_len; char* hex; struct object_id const* oid; struct repository* repo; } ;
struct disambiguate_state {int always_call_fn; void* cb_data; int /*<<< orphan*/  fn; } ;
struct TYPE_2__ {unsigned int hexsz; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int FALLBACK_DEFAULT_ABBREV ; 
 int /*<<< orphan*/  find_abbrev_len_packed (struct min_abbrev_data*) ; 
 int /*<<< orphan*/  find_short_object_filename (struct disambiguate_state*) ; 
 int /*<<< orphan*/  finish_object_disambiguation (struct disambiguate_state*,struct object_id*) ; 
 scalar_t__ init_object_disambiguation (struct repository*,char*,int,struct disambiguate_state*) ; 
 int msb (unsigned long) ; 
 int /*<<< orphan*/  oid_to_hex_r (char*,struct object_id const*) ; 
 unsigned long repo_approximate_object_count (struct repository*) ; 
 int /*<<< orphan*/  repo_extend_abbrev_len ; 

int repo_find_unique_abbrev_r(struct repository *r, char *hex,
			      const struct object_id *oid, int len)
{
	struct disambiguate_state ds;
	struct min_abbrev_data mad;
	struct object_id oid_ret;
	const unsigned hexsz = r->hash_algo->hexsz;

	if (len < 0) {
		unsigned long count = repo_approximate_object_count(r);
		/*
		 * Add one because the MSB only tells us the highest bit set,
		 * not including the value of all the _other_ bits (so "15"
		 * is only one off of 2^4, but the MSB is the 3rd bit.
		 */
		len = msb(count) + 1;
		/*
		 * We now know we have on the order of 2^len objects, which
		 * expects a collision at 2^(len/2). But we also care about hex
		 * chars, not bits, and there are 4 bits per hex. So all
		 * together we need to divide by 2 and round up.
		 */
		len = DIV_ROUND_UP(len, 2);
		/*
		 * For very small repos, we stick with our regular fallback.
		 */
		if (len < FALLBACK_DEFAULT_ABBREV)
			len = FALLBACK_DEFAULT_ABBREV;
	}

	oid_to_hex_r(hex, oid);
	if (len == hexsz || !len)
		return hexsz;

	mad.repo = r;
	mad.init_len = len;
	mad.cur_len = len;
	mad.hex = hex;
	mad.oid = oid;

	find_abbrev_len_packed(&mad);

	if (init_object_disambiguation(r, hex, mad.cur_len, &ds) < 0)
		return -1;

	ds.fn = repo_extend_abbrev_len;
	ds.always_call_fn = 1;
	ds.cb_data = (void *)&mad;

	find_short_object_filename(&ds);
	(void)finish_object_disambiguation(&ds, &oid_ret);

	hex[mad.cur_len] = 0;
	return mad.cur_len;
}