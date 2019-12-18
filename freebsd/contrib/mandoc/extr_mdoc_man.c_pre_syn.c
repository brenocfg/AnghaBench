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
struct roff_node {int flags; scalar_t__ tok; TYPE_1__* prev; } ;
struct TYPE_2__ {scalar_t__ tok; } ;

/* Variables and functions */
#define  MDOC_Fd 133 
#define  MDOC_Fn 132 
#define  MDOC_Fo 131 
#define  MDOC_Ft 130 
#define  MDOC_In 129 
#define  MDOC_Vt 128 
 int /*<<< orphan*/  MMAN_br ; 
 int /*<<< orphan*/  MMAN_sp ; 
 int NODE_SYNPRETTY ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static void
pre_syn(const struct roff_node *n)
{

	if (NULL == n->prev || ! (NODE_SYNPRETTY & n->flags))
		return;

	if (n->prev->tok == n->tok &&
	    MDOC_Ft != n->tok &&
	    MDOC_Fo != n->tok &&
	    MDOC_Fn != n->tok) {
		outflags |= MMAN_br;
		return;
	}

	switch (n->prev->tok) {
	case MDOC_Fd:
	case MDOC_Fn:
	case MDOC_Fo:
	case MDOC_In:
	case MDOC_Vt:
		outflags |= MMAN_sp;
		break;
	case MDOC_Ft:
		if (MDOC_Fn != n->tok && MDOC_Fo != n->tok) {
			outflags |= MMAN_sp;
			break;
		}
		/* FALLTHROUGH */
	default:
		outflags |= MMAN_br;
		break;
	}
}