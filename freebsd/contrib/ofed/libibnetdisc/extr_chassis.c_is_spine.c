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
typedef  int /*<<< orphan*/  ibnd_node_t ;

/* Variables and functions */
 scalar_t__ is_spine_2004 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spine_2012 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spine_4200 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spine_4700 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spine_4700x2 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spine_9096 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spine_9288 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_spine(ibnd_node_t * n)
{
	return (is_spine_9096(n) || is_spine_9288(n) ||
		is_spine_2004(n) || is_spine_2012(n) ||
		is_spine_4700(n) || is_spine_4700x2(n) ||
		is_spine_4200(n));
}