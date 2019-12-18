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
struct TYPE_2__ {int /*<<< orphan*/  aux_guid; } ;
typedef  TYPE_1__ spa_aux_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
spa_aux_compare(const void *a, const void *b)
{
	const spa_aux_t *sa = (const spa_aux_t *)a;
	const spa_aux_t *sb = (const spa_aux_t *)b;

	return (AVL_CMP(sa->aux_guid, sb->aux_guid));
}