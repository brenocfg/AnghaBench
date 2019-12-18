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
struct callback {struct callback* cb_next; void* cb_arg; int /*<<< orphan*/ * cb_func; } ;
typedef  int /*<<< orphan*/  callback_func ;

/* Variables and functions */
 struct callback* callbacks ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct callback* malloc (int) ; 

void
callback_register(callback_func *func, void *arg)
{
	struct callback *cb;

	cb = malloc(sizeof(struct callback));
	if (cb == NULL)
		errx(1, "unable to allocate memory for callback");
	cb->cb_func = func;
	cb->cb_arg = arg;
	cb->cb_next = callbacks;
	callbacks = cb;
}