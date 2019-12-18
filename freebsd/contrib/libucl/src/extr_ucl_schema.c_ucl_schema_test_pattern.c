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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucl_object_iterate (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const ucl_object_t *
ucl_schema_test_pattern (const ucl_object_t *obj, const char *pattern, bool recursive)
{
	const ucl_object_t *res = NULL;
#ifdef HAVE_REGEX_H
	regex_t reg;
	const ucl_object_t *elt;
	ucl_object_iter_t iter = NULL;

	if (regcomp (&reg, pattern, REG_EXTENDED | REG_NOSUB) == 0) {
		if (recursive) {
			while ((elt = ucl_object_iterate (obj, &iter, true)) != NULL) {
				if (regexec (&reg, ucl_object_key (elt), 0, NULL, 0) == 0) {
					res = elt;
					break;
				}
			}
		} else {
			if (regexec (&reg, ucl_object_key (obj), 0, NULL, 0) == 0)
				res = obj;
		}
		regfree (&reg);
	}
#endif
	return res;
}