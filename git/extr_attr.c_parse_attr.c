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
struct attr_state {int /*<<< orphan*/  attr; int /*<<< orphan*/  setto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR__FALSE ; 
 int /*<<< orphan*/  ATTR__TRUE ; 
 int /*<<< orphan*/  ATTR__UNSET ; 
 int /*<<< orphan*/  attr_name_valid (char const*,int) ; 
 int /*<<< orphan*/  blank ; 
 int /*<<< orphan*/  git_attr_internal (char const*,int) ; 
 int /*<<< orphan*/  report_invalid_attr (char const*,int,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strcspn (char const*,int /*<<< orphan*/ ) ; 
 int strspn (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmemdupz (char const*,int) ; 

__attribute__((used)) static const char *parse_attr(const char *src, int lineno, const char *cp,
			      struct attr_state *e)
{
	const char *ep, *equals;
	int len;

	ep = cp + strcspn(cp, blank);
	equals = strchr(cp, '=');
	if (equals && ep < equals)
		equals = NULL;
	if (equals)
		len = equals - cp;
	else
		len = ep - cp;
	if (!e) {
		if (*cp == '-' || *cp == '!') {
			cp++;
			len--;
		}
		if (!attr_name_valid(cp, len)) {
			report_invalid_attr(cp, len, src, lineno);
			return NULL;
		}
	} else {
		/*
		 * As this function is always called twice, once with
		 * e == NULL in the first pass and then e != NULL in
		 * the second pass, no need for attr_name_valid()
		 * check here.
		 */
		if (*cp == '-' || *cp == '!') {
			e->setto = (*cp == '-') ? ATTR__FALSE : ATTR__UNSET;
			cp++;
			len--;
		}
		else if (!equals)
			e->setto = ATTR__TRUE;
		else {
			e->setto = xmemdupz(equals + 1, ep - equals - 1);
		}
		e->attr = git_attr_internal(cp, len);
	}
	return ep + strspn(ep, blank);
}