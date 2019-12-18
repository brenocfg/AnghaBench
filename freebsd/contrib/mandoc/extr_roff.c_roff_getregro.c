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
struct roff {size_t mstackpos; TYPE_1__* mstack; } ;
struct TYPE_2__ {int argc; } ;

/* Variables and functions */

__attribute__((used)) static int
roff_getregro(const struct roff *r, const char *name)
{

	switch (*name) {
	case '$':  /* Number of arguments of the last macro evaluated. */
		return r->mstackpos < 0 ? 0 : r->mstack[r->mstackpos].argc;
	case 'A':  /* ASCII approximation mode is always off. */
		return 0;
	case 'g':  /* Groff compatibility mode is always on. */
		return 1;
	case 'H':  /* Fixed horizontal resolution. */
		return 24;
	case 'j':  /* Always adjust left margin only. */
		return 0;
	case 'T':  /* Some output device is always defined. */
		return 1;
	case 'V':  /* Fixed vertical resolution. */
		return 40;
	default:
		return -1;
	}
}