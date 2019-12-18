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
struct iter_qstate {int /*<<< orphan*/  final_state; } ;

/* Variables and functions */
 int next_state (struct iter_qstate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
final_state(struct iter_qstate* iq)
{
	return next_state(iq, iq->final_state);
}