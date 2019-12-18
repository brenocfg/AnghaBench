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
typedef  union dinode {int dummy; } dinode ;
struct inodesc {int /*<<< orphan*/  id_number; int /*<<< orphan*/  id_func; int /*<<< orphan*/  id_type; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int /*<<< orphan*/  ino_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
 int /*<<< orphan*/  USTATE ; 
 int /*<<< orphan*/  ckinode (union dinode*,struct inodesc*) ; 
 int /*<<< orphan*/  clearinode (union dinode*) ; 
 union dinode* ginode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 TYPE_1__* inoinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct inodesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_files ; 
 int /*<<< orphan*/  pass4check ; 

void
freeino(ino_t ino)
{
	struct inodesc idesc;
	union dinode *dp;

	memset(&idesc, 0, sizeof(struct inodesc));
	idesc.id_type = ADDR;
	idesc.id_func = pass4check;
	idesc.id_number = ino;
	dp = ginode(ino);
	(void)ckinode(dp, &idesc);
	clearinode(dp);
	inodirty(dp);
	inoinfo(ino)->ino_state = USTATE;
	n_files--;
}