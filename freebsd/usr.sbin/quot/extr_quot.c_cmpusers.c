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
struct user {int space; } ;

/* Variables and functions */

__attribute__((used)) static int
cmpusers(const void *v1, const void *v2)
{
	const struct user *u1, *u2;
	u1 = (const struct user *)v1;
	u2 = (const struct user *)v2;

	return u2->space - u1->space;
}