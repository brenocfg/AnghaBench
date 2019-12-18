#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* addr; scalar_t__ assocID; } ;
typedef  TYPE_1__ unpeer_node ;
typedef  int u_long ;
typedef  int u_char ;
typedef  scalar_t__ associd_t ;
struct TYPE_8__ {scalar_t__ address; } ;
typedef  TYPE_2__ address_node ;

/* Variables and functions */
 int ASSOCID_MAX ; 
 int /*<<< orphan*/  destroy_address_node (TYPE_2__*) ; 
 TYPE_1__* emalloc_zero (int) ; 
 scalar_t__ isdigit (int const) ; 

unpeer_node *
create_unpeer_node(
	address_node *addr
	)
{
	unpeer_node *	my_node;
	u_long		u;
	const u_char *	pch;

	my_node = emalloc_zero(sizeof(*my_node));

	/*
	 * From the parser's perspective an association ID fits into
	 * its generic T_String definition of a name/address "address".
	 * We treat all valid 16-bit numbers as association IDs.
	 */
	for (u = 0, pch = (u_char*)addr->address; isdigit(*pch); ++pch) {
		/* accumulate with overflow retention */
		u = (10 * u + *pch - '0') | (u & 0xFF000000u);
	}

	if (!*pch && u <= ASSOCID_MAX) {
		my_node->assocID = (associd_t)u;
		my_node->addr = NULL;
		destroy_address_node(addr);
	} else {
		my_node->assocID = 0;
		my_node->addr = addr;
	}

	return my_node;
}