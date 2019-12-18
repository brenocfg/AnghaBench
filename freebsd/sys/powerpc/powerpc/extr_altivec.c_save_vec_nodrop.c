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
struct thread {int dummy; } ;

/* Variables and functions */
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_vec_int (struct thread*) ; 
 int /*<<< orphan*/  vecthread ; 

void
save_vec_nodrop(struct thread *td)
{
	struct thread *vtd;

	vtd = PCPU_GET(vecthread);
	if (td != vtd) {
		return;
	}

	save_vec_int(td);
}