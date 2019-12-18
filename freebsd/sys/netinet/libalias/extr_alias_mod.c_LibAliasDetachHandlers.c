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
struct proto_handler {scalar_t__ dir; } ;

/* Variables and functions */
 scalar_t__ NODIR ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct proto_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handler_chain ; 
 int /*<<< orphan*/  link ; 

int
LibAliasDetachHandlers(struct proto_handler *p)
{

	while (p->dir != NODIR) {
		TAILQ_REMOVE(&handler_chain, p, link);
		p++;
	}

	return (0);
}