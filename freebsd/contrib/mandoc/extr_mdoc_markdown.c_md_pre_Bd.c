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
struct roff_node {TYPE_2__* norm; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ Bd; } ;

/* Variables and functions */
#define  DISP_literal 129 
#define  DISP_unfilled 128 
 int md_pre_D1 (struct roff_node*) ; 
 int md_pre_Dl (struct roff_node*) ; 

__attribute__((used)) static int
md_pre_Bd(struct roff_node *n)
{
	switch (n->norm->Bd.type) {
	case DISP_unfilled:
	case DISP_literal:
		return md_pre_Dl(n);
	default:
		return md_pre_D1(n);
	}
}