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
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 scalar_t__ havhash ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xhash ; 

void
dounhash(Char **v, struct command *c)
{
    USE(c);
    USE(v);
    havhash = 0;
#ifdef FASTHASH
    xfree(xhash);
    xhash = NULL;
#endif /* FASTHASH */
}