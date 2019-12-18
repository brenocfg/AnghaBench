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
struct inpcb {int /*<<< orphan*/  inp_route; } ;

/* Variables and functions */
 int /*<<< orphan*/  RO_INVALIDATE_CACHE (int /*<<< orphan*/ *) ; 

void
in_losing(struct inpcb *inp)
{

	RO_INVALIDATE_CACHE(&inp->inp_route);
	return;
}