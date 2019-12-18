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
struct lc_time_T {int dummy; } ;
struct xlocale_time {int /*<<< orphan*/  buffer; struct lc_time_T locale; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCTIME_SIZE ; 
 int __part_load_locale (char const*,int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int
time_load_locale(struct xlocale_time *l, int *using_locale, const char *name)
{
	struct lc_time_T *time_locale = &l->locale;
	return (__part_load_locale(name, using_locale,
			&l->buffer, "LC_TIME",
			LCTIME_SIZE, LCTIME_SIZE,
			(const char **)time_locale));
}