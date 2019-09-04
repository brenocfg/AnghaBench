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
 int checkpoint_requested ; 
 int /*<<< orphan*/  skip_optional_lf () ; 

__attribute__((used)) static void parse_checkpoint(void)
{
	checkpoint_requested = 1;
	skip_optional_lf();
}