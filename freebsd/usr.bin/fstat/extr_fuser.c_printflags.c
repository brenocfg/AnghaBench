#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct consumer {int uflags; int flags; } ;
struct TYPE_4__ {int flag; int /*<<< orphan*/  ch; } ;
struct TYPE_3__ {int flag; int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 unsigned int NFFLAGS ; 
 unsigned int NUFLAGS ; 
 int /*<<< orphan*/  assert (struct consumer*) ; 
 TYPE_2__* fflags ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* uflags ; 

__attribute__((used)) static void
printflags(struct consumer *cons)
{
	unsigned int i;

	assert(cons);
	for (i = 0; i < NUFLAGS; i++)
		if ((cons->uflags & uflags[i].flag) != 0)
			fputc(uflags[i].ch, stderr);
	for (i = 0; i < NFFLAGS; i++)
		if ((cons->flags & fflags[i].flag) != 0)
			fputc(fflags[i].ch, stderr);
}