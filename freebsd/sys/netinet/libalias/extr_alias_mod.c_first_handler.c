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
struct proto_handler {int dummy; } ;

/* Variables and functions */
 struct proto_handler* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handler_chain ; 

struct proto_handler *
first_handler(void)
{

	return (TAILQ_FIRST(&handler_chain));
}