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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int spa_asize_inflation ; 

uint64_t
spa_get_worst_case_asize(spa_t *spa, uint64_t lsize)
{
	return (lsize * spa_asize_inflation);
}