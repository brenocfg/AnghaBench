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
struct addrtree {int /*<<< orphan*/  (* sizefunc ) (scalar_t__) ;} ;
struct addrnode {scalar_t__ elem; TYPE_1__* parent_edge; } ;
struct TYPE_2__ {size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static inline size_t 
node_size(const struct addrtree *tree, const struct addrnode *n)
{
	return sizeof *n + sizeof *n->parent_edge + n->parent_edge->len + 
		(n->elem?tree->sizefunc(n->elem):0);
}