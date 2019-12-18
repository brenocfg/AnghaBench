#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  args; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned long lock_rtas () ; 
 TYPE_1__ rtas ; 
 int /*<<< orphan*/  rtas_call_unlocked (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  unlock_rtas (unsigned long) ; 

__attribute__((used)) static void call_rtas_display_status(unsigned char c)
{
	unsigned long s;

	if (!rtas.base)
		return;

	s = lock_rtas();
	rtas_call_unlocked(&rtas.args, 10, 1, 1, NULL, c);
	unlock_rtas(s);
}