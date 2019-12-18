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
struct typetable {int* table; int /*<<< orphan*/  nextarg; } ;
typedef  enum typeid { ____Placeholder_typeid } typeid ;

/* Variables and functions */
 scalar_t__ _ensurespace (struct typetable*) ; 

__attribute__((used)) static inline int
addtype(struct typetable *types, enum typeid type)
{

	if (_ensurespace(types))
		return (-1);
	types->table[types->nextarg++] = type;
	return (0);
}