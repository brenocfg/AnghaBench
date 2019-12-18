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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ref; } ;
typedef  TYPE_1__ subst_t ;

/* Variables and functions */
 int wcscmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
subst_compare_ref(const void *n1, const void *n2)
{
	const wchar_t *c1 = ((const subst_t *)n1)->ref;
	const wchar_t *c2 = ((const subst_t *)n2)->ref;
	int rv;

	rv = wcscmp(c1, c2);
	return ((rv < 0) ? -1 : (rv > 0) ? 1 : 0);
}