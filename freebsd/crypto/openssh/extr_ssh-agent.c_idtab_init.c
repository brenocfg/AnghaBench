#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nentries; int /*<<< orphan*/  idlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* idtab ; 
 TYPE_1__* xcalloc (int,int) ; 

__attribute__((used)) static void
idtab_init(void)
{
	idtab = xcalloc(1, sizeof(*idtab));
	TAILQ_INIT(&idtab->idlist);
	idtab->nentries = 0;
}