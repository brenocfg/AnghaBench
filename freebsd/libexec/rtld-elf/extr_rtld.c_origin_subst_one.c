#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* origin_path; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  obj_resolve_origin (TYPE_1__*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 
 char* xmalloc (int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
origin_subst_one(Obj_Entry *obj, char *real, const char *kw,
    const char *subst, bool may_free)
{
	char *p, *p1, *res, *resp;
	int subst_len, kw_len, subst_count, old_len, new_len;

	kw_len = strlen(kw);

	/*
	 * First, count the number of the keyword occurrences, to
	 * preallocate the final string.
	 */
	for (p = real, subst_count = 0;; p = p1 + kw_len, subst_count++) {
		p1 = strstr(p, kw);
		if (p1 == NULL)
			break;
	}

	/*
	 * If the keyword is not found, just return.
	 *
	 * Return non-substituted string if resolution failed.  We
	 * cannot do anything more reasonable, the failure mode of the
	 * caller is unresolved library anyway.
	 */
	if (subst_count == 0 || (obj != NULL && !obj_resolve_origin(obj)))
		return (may_free ? real : xstrdup(real));
	if (obj != NULL)
		subst = obj->origin_path;

	/*
	 * There is indeed something to substitute.  Calculate the
	 * length of the resulting string, and allocate it.
	 */
	subst_len = strlen(subst);
	old_len = strlen(real);
	new_len = old_len + (subst_len - kw_len) * subst_count;
	res = xmalloc(new_len + 1);

	/*
	 * Now, execute the substitution loop.
	 */
	for (p = real, resp = res, *resp = '\0';;) {
		p1 = strstr(p, kw);
		if (p1 != NULL) {
			/* Copy the prefix before keyword. */
			memcpy(resp, p, p1 - p);
			resp += p1 - p;
			/* Keyword replacement. */
			memcpy(resp, subst, subst_len);
			resp += subst_len;
			*resp = '\0';
			p = p1 + kw_len;
		} else
			break;
	}

	/* Copy to the end of string and finish. */
	strcat(resp, p);
	if (may_free)
		free(real);
	return (res);
}