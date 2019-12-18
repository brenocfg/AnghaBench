#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ token ;
typedef  scalar_t__ tok_kind ;

/* Variables and functions */
 int /*<<< orphan*/  get_token (TYPE_1__*) ; 
 int /*<<< orphan*/  peek (TYPE_1__*) ; 

int
peekscan(tok_kind expect, token *tokp)
{
	peek(tokp);
	if (tokp->kind == expect) {
		get_token(tokp);
		return (1);
	}
	return (0);
}