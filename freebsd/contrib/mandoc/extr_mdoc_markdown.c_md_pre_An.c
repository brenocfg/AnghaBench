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
struct roff_node {int /*<<< orphan*/  sec; TYPE_2__* norm; } ;
struct TYPE_3__ {int auth; } ;
struct TYPE_4__ {TYPE_1__ An; } ;

/* Variables and functions */
#define  AUTH_nosplit 129 
#define  AUTH_split 128 
 int MD_An_nosplit ; 
 int MD_An_split ; 
 int MD_br ; 
 int /*<<< orphan*/  SEC_AUTHORS ; 
 int outflags ; 

__attribute__((used)) static int
md_pre_An(struct roff_node *n)
{
	switch (n->norm->An.auth) {
	case AUTH_split:
		outflags &= ~MD_An_nosplit;
		outflags |= MD_An_split;
		return 0;
	case AUTH_nosplit:
		outflags &= ~MD_An_split;
		outflags |= MD_An_nosplit;
		return 0;
	default:
		if (outflags & MD_An_split)
			outflags |= MD_br;
		else if (n->sec == SEC_AUTHORS &&
		    ! (outflags & MD_An_nosplit))
			outflags |= MD_An_split;
		return 1;
	}
}