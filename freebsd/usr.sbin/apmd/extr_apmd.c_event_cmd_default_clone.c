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
struct event_cmd {int /*<<< orphan*/  op; int /*<<< orphan*/  name; int /*<<< orphan*/  len; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 struct event_cmd* malloc (int /*<<< orphan*/ ) ; 

struct event_cmd *
event_cmd_default_clone(void *this)
{
	struct event_cmd * oldone = this;
	struct event_cmd * newone = malloc(oldone->len);

	newone->next = NULL;
	newone->len = oldone->len;
	newone->name = oldone->name;
	newone->op = oldone->op;
	return newone;
}