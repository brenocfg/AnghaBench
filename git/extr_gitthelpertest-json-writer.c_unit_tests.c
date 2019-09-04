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
 int /*<<< orphan*/  arr1 ; 
 int /*<<< orphan*/  arr2 ; 
 int /*<<< orphan*/  arr3 ; 
 int /*<<< orphan*/  arr4 ; 
 int /*<<< orphan*/  inline1 ; 
 int /*<<< orphan*/  inline2 ; 
 int /*<<< orphan*/  jw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixed1 ; 
 int /*<<< orphan*/  nest1 ; 
 int /*<<< orphan*/  obj1 ; 
 int /*<<< orphan*/  obj2 ; 
 int /*<<< orphan*/  obj3 ; 
 int /*<<< orphan*/  obj4 ; 
 int /*<<< orphan*/  obj5 ; 
 int /*<<< orphan*/  obj6 ; 
 int /*<<< orphan*/  p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unit_tests(void)
{
	/* comptact (canonical) forms */
	t(obj1);
	t(obj2);
	t(obj3);
	t(obj4);
	t(obj5);
	t(obj6);

	t(arr1);
	t(arr2);
	t(arr3);
	t(arr4);

	t(nest1);

	t(inline1);
	t(inline2);

	jw_init(&obj1);
	jw_init(&obj2);
	jw_init(&obj3);
	jw_init(&obj4);

	jw_init(&arr1);
	jw_init(&arr2);
	jw_init(&arr3);
	jw_init(&arr4);

	jw_init(&inline1);
	jw_init(&inline2);

	/* pretty forms */
	p(obj1);
	p(obj2);
	p(obj3);
	p(obj4);

	p(arr1);
	p(arr2);
	p(arr3);
	p(arr4);

	p(inline1);
	p(inline2);

	/* mixed forms */
	t(mixed1);
	jw_init(&mixed1);
	p(mixed1);

	return 0;
}