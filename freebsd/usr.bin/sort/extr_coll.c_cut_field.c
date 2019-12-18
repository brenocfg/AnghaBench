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
struct key_specs {int dummy; } ;
struct bwstring {int dummy; } ;

/* Variables and functions */
 struct bwstring* bwsalloc (size_t) ; 
 int /*<<< orphan*/  bwsnocpy (struct bwstring*,struct bwstring const*,size_t,size_t) ; 
 size_t find_field_end (struct bwstring const*,struct key_specs*) ; 
 int /*<<< orphan*/  find_field_start (struct bwstring const*,struct key_specs*,size_t*,size_t*,int*,int*) ; 

__attribute__((used)) static struct bwstring *
cut_field(const struct bwstring *s, struct key_specs *ks)
{
	struct bwstring *ret = NULL;

	if (s && ks) {
		size_t field_start, key_end, key_start, sz;
		bool empty_field, empty_key;

		field_start = 0;
		key_start = 0;
		empty_field = false;
		empty_key = false;

		find_field_start(s, ks, &field_start, &key_start,
		    &empty_field, &empty_key);

		if (empty_key)
			sz = 0;
		else {
			key_end = find_field_end(s, ks);
			sz = (key_end < key_start) ? 0 : (key_end - key_start);
		}

		ret = bwsalloc(sz);
		if (sz)
			bwsnocpy(ret, s, key_start, sz);
	} else
		ret = bwsalloc(0);

	return (ret);
}