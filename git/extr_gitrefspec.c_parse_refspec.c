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
struct refspec_item {int force; int matching; int pattern; int exact_sha1; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {size_t hexsz; } ;

/* Variables and functions */
 int REFNAME_ALLOW_ONELEVEL ; 
 int REFNAME_REFSPEC_PATTERN ; 
 scalar_t__ check_refname_format (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_oid_hex (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ memchr (char const*,char,size_t) ; 
 scalar_t__ strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 TYPE_1__* the_hash_algo ; 
 void* xstrndup (char const*,size_t) ; 

__attribute__((used)) static int parse_refspec(struct refspec_item *item, const char *refspec, int fetch)
{
	size_t llen;
	int is_glob;
	const char *lhs, *rhs;
	int flags;

	is_glob = 0;

	lhs = refspec;
	if (*lhs == '+') {
		item->force = 1;
		lhs++;
	}

	rhs = strrchr(lhs, ':');

	/*
	 * Before going on, special case ":" (or "+:") as a refspec
	 * for pushing matching refs.
	 */
	if (!fetch && rhs == lhs && rhs[1] == '\0') {
		item->matching = 1;
		return 1;
	}

	if (rhs) {
		size_t rlen = strlen(++rhs);
		is_glob = (1 <= rlen && strchr(rhs, '*'));
		item->dst = xstrndup(rhs, rlen);
	} else {
		item->dst = NULL;
	}

	llen = (rhs ? (rhs - lhs - 1) : strlen(lhs));
	if (1 <= llen && memchr(lhs, '*', llen)) {
		if ((rhs && !is_glob) || (!rhs && fetch))
			return 0;
		is_glob = 1;
	} else if (rhs && is_glob) {
		return 0;
	}

	item->pattern = is_glob;
	item->src = xstrndup(lhs, llen);
	flags = REFNAME_ALLOW_ONELEVEL | (is_glob ? REFNAME_REFSPEC_PATTERN : 0);

	if (fetch) {
		struct object_id unused;

		/* LHS */
		if (!*item->src)
			; /* empty is ok; it means "HEAD" */
		else if (llen == the_hash_algo->hexsz && !get_oid_hex(item->src, &unused))
			item->exact_sha1 = 1; /* ok */
		else if (!check_refname_format(item->src, flags))
			; /* valid looking ref is ok */
		else
			return 0;
		/* RHS */
		if (!item->dst)
			; /* missing is ok; it is the same as empty */
		else if (!*item->dst)
			; /* empty is ok; it means "do not store" */
		else if (!check_refname_format(item->dst, flags))
			; /* valid looking ref is ok */
		else
			return 0;
	} else {
		/*
		 * LHS
		 * - empty is allowed; it means delete.
		 * - when wildcarded, it must be a valid looking ref.
		 * - otherwise, it must be an extended SHA-1, but
		 *   there is no existing way to validate this.
		 */
		if (!*item->src)
			; /* empty is ok */
		else if (is_glob) {
			if (check_refname_format(item->src, flags))
				return 0;
		}
		else
			; /* anything goes, for now */
		/*
		 * RHS
		 * - missing is allowed, but LHS then must be a
		 *   valid looking ref.
		 * - empty is not allowed.
		 * - otherwise it must be a valid looking ref.
		 */
		if (!item->dst) {
			if (check_refname_format(item->src, flags))
				return 0;
		} else if (!*item->dst) {
			return 0;
		} else {
			if (check_refname_format(item->dst, flags))
				return 0;
		}
	}

	return 1;
}