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
struct refspec {int nr; int /*<<< orphan*/ * items; } ;
struct ref {int dummy; } ;

/* Variables and functions */
 scalar_t__ match_explicit (struct ref*,struct ref*,struct ref***,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int match_explicit_refs(struct ref *src, struct ref *dst,
			       struct ref ***dst_tail, struct refspec *rs)
{
	int i, errs;
	for (i = errs = 0; i < rs->nr; i++)
		errs += match_explicit(src, dst, dst_tail, &rs->items[i]);
	return errs;
}