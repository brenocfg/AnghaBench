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
struct TYPE_2__ {int /*<<< orphan*/ * sym; } ;
struct expr {scalar_t__ type; TYPE_1__ left; } ;

/* Variables and functions */
 scalar_t__ E_SYMBOL ; 
 int /*<<< orphan*/  symbol_no ; 

__attribute__((used)) static inline int expr_is_no(struct expr *e)
{
	return e && (e->type == E_SYMBOL && e->left.sym == &symbol_no);
}