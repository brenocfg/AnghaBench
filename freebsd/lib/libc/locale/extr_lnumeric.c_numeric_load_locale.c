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
struct lc_numeric_T {char* decimal_point; int /*<<< orphan*/  grouping; } ;
struct xlocale_numeric {int /*<<< orphan*/  buffer; struct lc_numeric_T locale; } ;
struct TYPE_2__ {char* decimal_point; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCNUMERIC_SIZE ; 
 TYPE_1__ _C_numeric_locale ; 
 int _LDP_ERROR ; 
 int _LDP_LOADED ; 
 int /*<<< orphan*/  __fix_locale_grouping_str (int /*<<< orphan*/ ) ; 
 int __part_load_locale (char const*,int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int
numeric_load_locale(struct xlocale_numeric *loc, int *using_locale, int *changed,
		const char *name)
{
	int ret;
	struct lc_numeric_T *l = &loc->locale;

	ret = __part_load_locale(name, using_locale,
		&loc->buffer, "LC_NUMERIC",
		LCNUMERIC_SIZE, LCNUMERIC_SIZE,
		(const char**)l);
	if (ret != _LDP_ERROR)
		*changed= 1;
	if (ret == _LDP_LOADED) {
		/* Can't be empty according to C99 */
		if (*l->decimal_point == '\0')
			l->decimal_point =
			    _C_numeric_locale.decimal_point;
		l->grouping =
		    __fix_locale_grouping_str(l->grouping);
	}
	return (ret);
}