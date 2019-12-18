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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 scalar_t__ MACRO_MAX ; 
 char* dbm_get (int /*<<< orphan*/ ) ; 
 TYPE_1__** macros ; 
 scalar_t__* nvals ; 

__attribute__((used)) static char *
macro_bypage(int32_t arg_im, int32_t arg_ip)
{
	static const int32_t	*pp;
	static int32_t		 im, ip, iv;

	/* Initialize for a new iteration. */

	if (arg_im < MACRO_MAX && arg_ip != 0) {
		im = arg_im;
		ip = arg_ip;
		pp = dbm_get(macros[im]->pages);
		iv = 0;
		return NULL;
	}
	if (im >= MACRO_MAX)
		return NULL;

	/* Search for the next value. */

	while (iv < nvals[im]) {
		if (*pp == ip)
			break;
		if (*pp == 0)
			iv++;
		pp++;
	}

	/* Reached the end without a match. */

	if (iv == nvals[im]) {
		im = MACRO_MAX;
		ip = 0;
		pp = NULL;
		return NULL;
	}

	/* Found a match; skip the remaining pages of this entry. */

	if (++iv < nvals[im])
		while (*pp++ != 0)
			continue;

	return dbm_get(macros[im][iv - 1].value);
}