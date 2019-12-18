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
struct iter_hints_stub {int /*<<< orphan*/  dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  delegpt_free_mlc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iter_hints_stub*) ; 

__attribute__((used)) static void hints_stub_free(struct iter_hints_stub* s)
{
	if(!s) return;
	delegpt_free_mlc(s->dp);
	free(s);
}