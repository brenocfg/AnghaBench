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
typedef  enum ops_t { ____Placeholder_ops_t } ops_t ;

/* Variables and functions */
 int FALSE ; 
#define  OP_EQL 131 
#define  OP_GEQ 130 
#define  OP_LEQ 129 
#define  OP_NONE 128 
 int TRUE ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
aq_revcmp(int revision, enum ops_t op, int value)
{
    switch (op) {
    case OP_LEQ:
	if (revision <= value)
	    return (TRUE);
	break;
    case OP_GEQ:
	if (revision >= value)
	    return (TRUE);
	break;
    case OP_EQL:
	if (revision == value)
	    return (TRUE);
	break;
    case OP_NONE:
	return (TRUE);
    default:
	panic("aq_revcmp: invalid op %d", op);
    }

    return (FALSE);
}