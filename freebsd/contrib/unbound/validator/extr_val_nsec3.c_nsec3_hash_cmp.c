#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct nsec3_cached_hash {int /*<<< orphan*/  rr; int /*<<< orphan*/  nsec3; int /*<<< orphan*/  dname; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ nsec3_get_algo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nsec3_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsec3_get_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nsec3_hash_cmp(const void* c1, const void* c2) 
{
	struct nsec3_cached_hash* h1 = (struct nsec3_cached_hash*)c1;
	struct nsec3_cached_hash* h2 = (struct nsec3_cached_hash*)c2;
	uint8_t* s1, *s2;
	size_t s1len, s2len;
	int c = query_dname_compare(h1->dname, h2->dname);
	if(c != 0)
		return c;
	/* compare parameters */
	/* if both malformed, its equal, robustness */
	if(nsec3_get_algo(h1->nsec3, h1->rr) !=
		nsec3_get_algo(h2->nsec3, h2->rr)) {
		if(nsec3_get_algo(h1->nsec3, h1->rr) <
			nsec3_get_algo(h2->nsec3, h2->rr))
			return -1;
		return 1;
	}
	if(nsec3_get_iter(h1->nsec3, h1->rr) !=
		nsec3_get_iter(h2->nsec3, h2->rr)) {
		if(nsec3_get_iter(h1->nsec3, h1->rr) <
			nsec3_get_iter(h2->nsec3, h2->rr))
			return -1;
		return 1;
	}
	(void)nsec3_get_salt(h1->nsec3, h1->rr, &s1, &s1len);
	(void)nsec3_get_salt(h2->nsec3, h2->rr, &s2, &s2len);
	if(s1len == 0 && s2len == 0)
		return 0;
	if(!s1) return -1;
	if(!s2) return 1;
	if(s1len != s2len) {
		if(s1len < s2len)
			return -1;
		return 1;
	}
	return memcmp(s1, s2, s1len);
}