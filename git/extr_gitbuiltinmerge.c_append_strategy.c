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
struct strategy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct strategy**,scalar_t__,int /*<<< orphan*/ ) ; 
 struct strategy** use_strategies ; 
 int /*<<< orphan*/  use_strategies_alloc ; 
 scalar_t__ use_strategies_nr ; 

__attribute__((used)) static void append_strategy(struct strategy *s)
{
	ALLOC_GROW(use_strategies, use_strategies_nr + 1, use_strategies_alloc);
	use_strategies[use_strategies_nr++] = s;
}