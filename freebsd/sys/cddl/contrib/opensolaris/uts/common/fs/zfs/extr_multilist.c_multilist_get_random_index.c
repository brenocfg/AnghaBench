#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ml_num_sublists; } ;
typedef  TYPE_1__ multilist_t ;

/* Variables and functions */
 unsigned int spa_get_random (int /*<<< orphan*/ ) ; 

unsigned int
multilist_get_random_index(multilist_t *ml)
{
	return (spa_get_random(ml->ml_num_sublists));
}