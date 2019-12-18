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
 int /*<<< orphan*/  fputhread ; 
 int /*<<< orphan*/  save_fpu_int (struct thread*) ; 

void
save_fpu_nodrop(struct thread *td)
{
	struct thread *ftd;

	ftd = PCPU_GET(fputhread);
	if (td != ftd) {
		return;
	}

	save_fpu_int(td);
}