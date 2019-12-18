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
struct termp {int dummy; } ;

/* Variables and functions */
 size_t term_strlen (struct termp*,char const*) ; 
 int /*<<< orphan*/  term_word (struct termp*,char const*) ; 

__attribute__((used)) static void
tbl_fill_string(struct termp *tp, const char *cp, size_t len)
{
	size_t	 i, sz;

	sz = term_strlen(tp, cp);
	for (i = 0; i < len; i += sz)
		term_word(tp, cp);
}