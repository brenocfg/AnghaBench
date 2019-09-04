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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int git_oid__cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int git_oid_cmp(const git_oid *a, const git_oid *b)
{
	return git_oid__cmp(a, b);
}