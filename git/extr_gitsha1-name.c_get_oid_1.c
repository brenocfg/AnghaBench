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
struct object_id {int dummy; } ;
typedef  enum get_oid_result { ____Placeholder_get_oid_result } get_oid_result ;

/* Variables and functions */
 int FOUND ; 
 int get_describe_name (char const*,int,struct object_id*) ; 
 int get_nth_ancestor (char const*,int,struct object_id*,int) ; 
 int get_oid_basic (char const*,int,struct object_id*,unsigned int) ; 
 int get_parent (char const*,int,struct object_id*,int) ; 
 int get_short_oid (char const*,int,struct object_id*,unsigned int) ; 
 int peel_onion (char const*,int,struct object_id*,unsigned int) ; 

__attribute__((used)) static enum get_oid_result get_oid_1(const char *name, int len,
				     struct object_id *oid,
				     unsigned lookup_flags)
{
	int ret, has_suffix;
	const char *cp;

	/*
	 * "name~3" is "name^^^", "name~" is "name~1", and "name^" is "name^1".
	 */
	has_suffix = 0;
	for (cp = name + len - 1; name <= cp; cp--) {
		int ch = *cp;
		if ('0' <= ch && ch <= '9')
			continue;
		if (ch == '~' || ch == '^')
			has_suffix = ch;
		break;
	}

	if (has_suffix) {
		int num = 0;
		int len1 = cp - name;
		cp++;
		while (cp < name + len)
			num = num * 10 + *cp++ - '0';
		if (!num && len1 == len - 1)
			num = 1;
		if (has_suffix == '^')
			return get_parent(name, len1, oid, num);
		/* else if (has_suffix == '~') -- goes without saying */
		return get_nth_ancestor(name, len1, oid, num);
	}

	ret = peel_onion(name, len, oid, lookup_flags);
	if (!ret)
		return FOUND;

	ret = get_oid_basic(name, len, oid, lookup_flags);
	if (!ret)
		return FOUND;

	/* It could be describe output that is "SOMETHING-gXXXX" */
	ret = get_describe_name(name, len, oid);
	if (!ret)
		return FOUND;

	return get_short_oid(name, len, oid, lookup_flags);
}