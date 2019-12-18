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
struct typetable {int /*<<< orphan*/  nextarg; int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 int INTMAXT ; 
 int LLONGINT ; 
 int LONGINT ; 
 int PTRDIFFT ; 
 int SIZET ; 
 int /*<<< orphan*/  T_INT ; 
 int /*<<< orphan*/  T_INTMAXT ; 
 int /*<<< orphan*/  T_LLONG ; 
 int /*<<< orphan*/  T_LONG ; 
 int /*<<< orphan*/  T_PTRDIFFT ; 
 int /*<<< orphan*/  T_SSIZET ; 
 scalar_t__ _ensurespace (struct typetable*) ; 

__attribute__((used)) static inline int
addsarg(struct typetable *types, int flags)
{

	if (_ensurespace(types))
		return (-1);
	if (flags & INTMAXT)
		types->table[types->nextarg++] = T_INTMAXT;
	else if (flags & SIZET)
		types->table[types->nextarg++] = T_SSIZET;
	else if (flags & PTRDIFFT)
		types->table[types->nextarg++] = T_PTRDIFFT;
	else if (flags & LLONGINT)
		types->table[types->nextarg++] = T_LLONG;
	else if (flags & LONGINT)
		types->table[types->nextarg++] = T_LONG;
	else
		types->table[types->nextarg++] = T_INT;
	return (0);
}