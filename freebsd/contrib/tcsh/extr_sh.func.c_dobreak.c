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
typedef  int /*<<< orphan*/ * command ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_NOTWHILE ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  noexec ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  toend () ; 
 int /*<<< orphan*/ * whyles ; 

void
dobreak(Char **v, struct command *c)
{
    USE(v);
    USE(c);
    if (whyles == NULL)
	stderror(ERR_NAME | ERR_NOTWHILE);
    if (!noexec)
	toend();
}