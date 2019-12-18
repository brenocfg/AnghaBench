#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {unsigned int keylen; scalar_t__ key; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
 void** lc_map ; 
 int /*<<< orphan*/  mum_hash_finish (scalar_t__) ; 
 scalar_t__ mum_hash_step (scalar_t__,scalar_t__) ; 
 scalar_t__ ucl_hash_seed () ; 

__attribute__((used)) static inline uint32_t
ucl_hash_caseless_func (const ucl_object_t *o)
{
	unsigned len = o->keylen;
	unsigned leftover = o->keylen % 8;
	unsigned fp, i;
	const uint8_t* s = (const uint8_t*)o->key;
	union {
		struct {
			unsigned char c1, c2, c3, c4, c5, c6, c7, c8;
		} c;
		uint64_t pp;
	} u;
	uint64_t r;

	fp = len - leftover;
	r = ucl_hash_seed ();

	for (i = 0; i != fp; i += 8) {
		u.c.c1 = s[i], u.c.c2 = s[i + 1], u.c.c3 = s[i + 2], u.c.c4 = s[i + 3];
		u.c.c5 = s[i + 4], u.c.c6 = s[i + 5], u.c.c7 = s[i + 6], u.c.c8 = s[i + 7];
		u.c.c1 = lc_map[u.c.c1];
		u.c.c2 = lc_map[u.c.c2];
		u.c.c3 = lc_map[u.c.c3];
		u.c.c4 = lc_map[u.c.c4];
		u.c.c1 = lc_map[u.c.c5];
		u.c.c2 = lc_map[u.c.c6];
		u.c.c3 = lc_map[u.c.c7];
		u.c.c4 = lc_map[u.c.c8];
		r = mum_hash_step (r, u.pp);
	}

	u.pp = 0;
	switch (leftover) {
	case 7:
		u.c.c7 = lc_map[(unsigned char)s[i++]];
	case 6:
		u.c.c6 = lc_map[(unsigned char)s[i++]];
	case 5:
		u.c.c5 = lc_map[(unsigned char)s[i++]];
	case 4:
		u.c.c4 = lc_map[(unsigned char)s[i++]];
	case 3:
		u.c.c3 = lc_map[(unsigned char)s[i++]];
	case 2:
		u.c.c2 = lc_map[(unsigned char)s[i++]];
	case 1:
		u.c.c1 = lc_map[(unsigned char)s[i]];
		r = mum_hash_step (r, u.pp);
		break;
	}

	return mum_hash_finish (r);
}