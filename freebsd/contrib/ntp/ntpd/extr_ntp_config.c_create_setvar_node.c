#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* var; char* val; int isdefault; } ;
typedef  TYPE_1__ setvar_node ;

/* Variables and functions */
 TYPE_1__* emalloc_zero (int) ; 
 char* strchr (char*,char) ; 

setvar_node *
create_setvar_node(
	char *	var,
	char *	val,
	int	isdefault
	)
{
	setvar_node *	my_node;
	char *		pch;

	/* do not allow = in the variable name */
	pch = strchr(var, '=');
	if (NULL != pch)
		*pch = '\0';

	/* Now store the string into a setvar_node */
	my_node = emalloc_zero(sizeof(*my_node));
	my_node->var = var;
	my_node->val = val;
	my_node->isdefault = isdefault;

	return my_node;
}