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
struct TYPE_2__ {int /*<<< orphan*/  spa_name; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int AVL_ISIGN (int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_name_compare(const void *a1, const void *a2)
{
	const spa_t *s1 = a1;
	const spa_t *s2 = a2;
	int s;

	s = strcmp(s1->spa_name, s2->spa_name);

	return (AVL_ISIGN(s));
}