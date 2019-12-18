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
struct passwd {int pw_uid; } ;

/* Variables and functions */

__attribute__((used)) static int
pwd_cmp_byuid(const void *ap, const void *bp)
{
	const struct passwd *a = ap;
	const struct passwd *b = bp;

	return (a->pw_uid - b->pw_uid);
}