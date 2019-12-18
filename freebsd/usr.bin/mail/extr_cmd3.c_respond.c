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

/* Variables and functions */
 int doRespond (int*) ; 
 int dorespond (int*) ; 
 int /*<<< orphan*/ * value (char*) ; 

int
respond(void *v)
{
	int *msgvec = v;

	if (value("Replyall") == NULL && value("flipr") == NULL)
		return (dorespond(msgvec));
	else
		return (doRespond(msgvec));
}