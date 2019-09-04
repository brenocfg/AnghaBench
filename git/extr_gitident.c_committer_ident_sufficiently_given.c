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
 int /*<<< orphan*/  committer_ident_explicitly_given ; 
 int ident_is_sufficient (int /*<<< orphan*/ ) ; 

int committer_ident_sufficiently_given(void)
{
	return ident_is_sufficient(committer_ident_explicitly_given);
}