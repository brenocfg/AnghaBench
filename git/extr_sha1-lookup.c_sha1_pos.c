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
typedef  int /*<<< orphan*/  (* sha1_access_fn ) (size_t,void*) ;
struct TYPE_2__ {int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int hashcmp (int /*<<< orphan*/ ,unsigned char const*) ; 
 int index_pos_to_insert_pos (size_t) ; 
 size_t take2 (unsigned char const*) ; 
 TYPE_1__* the_hash_algo ; 

int sha1_pos(const unsigned char *hash, void *table, size_t nr,
	     sha1_access_fn fn)
{
	size_t hi = nr;
	size_t lo = 0;
	size_t mi = 0;

	if (!nr)
		return -1;

	if (nr != 1) {
		size_t lov, hiv, miv, ofs;

		for (ofs = 0; ofs < the_hash_algo->rawsz - 2; ofs += 2) {
			lov = take2(fn(0, table) + ofs);
			hiv = take2(fn(nr - 1, table) + ofs);
			miv = take2(hash + ofs);
			if (miv < lov)
				return -1;
			if (hiv < miv)
				return index_pos_to_insert_pos(nr);
			if (lov != hiv) {
				/*
				 * At this point miv could be equal
				 * to hiv (but sha1 could still be higher);
				 * the invariant of (mi < hi) should be
				 * kept.
				 */
				mi = (nr - 1) * (miv - lov) / (hiv - lov);
				if (lo <= mi && mi < hi)
					break;
				BUG("assertion failed in binary search");
			}
		}
	}

	do {
		int cmp;
		cmp = hashcmp(fn(mi, table), hash);
		if (!cmp)
			return mi;
		if (cmp > 0)
			hi = mi;
		else
			lo = mi + 1;
		mi = lo + (hi - lo) / 2;
	} while (lo < hi);
	return index_pos_to_insert_pos(lo);
}