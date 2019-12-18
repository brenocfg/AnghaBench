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
struct page {int dummy; } ;
struct dbm_res {int member_0; struct page* page; int /*<<< orphan*/  member_1; } ;
struct dbm_match {int dummy; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  pages; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ITER_MACRO ; 
 scalar_t__ ITER_NONE ; 
 size_t MACRO_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dbm_get (int /*<<< orphan*/ ) ; 
 scalar_t__ dbm_match (struct dbm_match const*,char const*) ; 
 scalar_t__ iteration ; 
 TYPE_1__** macros ; 
 int* nvals ; 
 int pages ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static struct dbm_res
page_bymacro(int32_t arg_im, const struct dbm_match *arg_match)
{
	static const struct dbm_match	*match;
	static const int32_t		*pp;
	static const char		*cp;
	static int32_t			 im, iv;
	struct dbm_res			 res = {-1, 0};

	assert(im >= 0);
	assert(im < MACRO_MAX);

	/* Initialize for a new iteration. */

	if (arg_match != NULL) {
		iteration = ITER_MACRO;
		match = arg_match;
		im = arg_im;
		cp = nvals[im] ? dbm_get(macros[im]->value) : NULL;
		pp = NULL;
		iv = -1;
		return res;
	}
	if (iteration != ITER_MACRO)
		return res;

	/* Find the next matching macro value. */

	while (pp == NULL || *pp == 0) {
		if (++iv == nvals[im]) {
			iteration = ITER_NONE;
			return res;
		}
		if (iv)
			cp = strchr(cp, '\0') + 1;
		if (dbm_match(match, cp))
			pp = dbm_get(macros[im][iv].pages);
	}

	/* Found a matching page. */

	res.page = (struct page *)dbm_get(*pp++) - pages;
	return res;
}