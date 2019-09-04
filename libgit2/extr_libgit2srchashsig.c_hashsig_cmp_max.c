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
typedef  scalar_t__ hashsig_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int hashsig_cmp_max(const void *a, const void *b, void *payload)
{
	hashsig_t av = *(const hashsig_t *)a, bv = *(const hashsig_t *)b;
	GIT_UNUSED(payload);
	return (av < bv) ? -1 : (av > bv) ? 1 : 0;
}