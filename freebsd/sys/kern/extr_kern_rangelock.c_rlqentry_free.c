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
struct rl_q_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rl_entry_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct rl_q_entry*) ; 

void
rlqentry_free(struct rl_q_entry *rleq)
{

	uma_zfree(rl_entry_zone, rleq);
}