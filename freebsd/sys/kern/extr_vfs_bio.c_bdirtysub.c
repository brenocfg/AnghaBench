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
struct bufdomain {int bd_lodirtybuffers; int bd_hidirtybuffers; int /*<<< orphan*/  bd_numdirtybuffers; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bd_clear (struct bufdomain*) ; 
 int /*<<< orphan*/  bdirtywakeup () ; 
 struct bufdomain* bufdomain (struct buf*) ; 

__attribute__((used)) static void
bdirtysub(struct buf *bp)
{
	struct bufdomain *bd;
	int num;

	bd = bufdomain(bp);
	num = atomic_fetchadd_int(&bd->bd_numdirtybuffers, -1);
	if (num == (bd->bd_lodirtybuffers + bd->bd_hidirtybuffers) / 2)
		bdirtywakeup();
	if (num == bd->bd_lodirtybuffers || num == bd->bd_hidirtybuffers)
		bd_clear(bd);
}