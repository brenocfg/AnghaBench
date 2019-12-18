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

/* Variables and functions */
 int /*<<< orphan*/  grep_realloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  lnbuf ; 
 size_t lnbuflen ; 

__attribute__((used)) static inline int
grep_lnbufgrow(size_t newlen)
{

	if (lnbuflen < newlen) {
		lnbuf = grep_realloc(lnbuf, newlen);
		lnbuflen = newlen;
	}

	return (0);
}