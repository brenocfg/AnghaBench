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
 scalar_t__ is_line_2024 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_line_24 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_line_4700 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_line_8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_line(ibnd_node_t * n)
{
	return (is_line_24(n) || is_line_8(n) ||
		is_line_2024(n) || is_line_4700(n));
}