#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  peerflags; } ;
typedef  TYPE_2__ peer_node ;
struct TYPE_6__ {int i; } ;
struct TYPE_8__ {TYPE_1__ value; struct TYPE_8__* link; } ;
typedef  TYPE_3__ attr_val ;

/* Variables and functions */
 int FLAG_BURST ; 
 int FLAG_IBURST ; 
 int FLAG_NOSELECT ; 
 int FLAG_PREEMPT ; 
 int FLAG_PREFER ; 
 int FLAG_SKEY ; 
 int FLAG_TRUE ; 
 int FLAG_XLEAVE ; 
 TYPE_3__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
#define  T_Autokey 135 
#define  T_Burst 134 
#define  T_Iburst 133 
#define  T_Noselect 132 
#define  T_Preempt 131 
#define  T_Prefer 130 
#define  T_True 129 
#define  T_Xleave 128 
 int /*<<< orphan*/  fatal_error (char*,int) ; 

__attribute__((used)) static int
peerflag_bits(
	peer_node *pn
	)
{
	int peerflags;
	attr_val *option;

	/* translate peerflags options to bits */
	peerflags = 0;
	option = HEAD_PFIFO(pn->peerflags);
	for (; option != NULL; option = option->link) {
		switch (option->value.i) {

		default:
			fatal_error("peerflag_bits: option-token=%d", option->value.i);

		case T_Autokey:
			peerflags |= FLAG_SKEY;
			break;

		case T_Burst:
			peerflags |= FLAG_BURST;
			break;

		case T_Iburst:
			peerflags |= FLAG_IBURST;
			break;

		case T_Noselect:
			peerflags |= FLAG_NOSELECT;
			break;

		case T_Preempt:
			peerflags |= FLAG_PREEMPT;
			break;

		case T_Prefer:
			peerflags |= FLAG_PREFER;
			break;

		case T_True:
			peerflags |= FLAG_TRUE;
			break;

		case T_Xleave:
			peerflags |= FLAG_XLEAVE;
			break;
		}
	}

	return peerflags;
}