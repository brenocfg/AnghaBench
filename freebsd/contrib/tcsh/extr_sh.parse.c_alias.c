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
struct wordent {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int ALEFT ; 
 int /*<<< orphan*/  ERR_ALIASLOOP ; 
 int /*<<< orphan*/  HLEFT ; 
 scalar_t__ asyntax (int /*<<< orphan*/ ,struct wordent*) ; 
 int /*<<< orphan*/  hleft ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 

void
alias(struct wordent *lexp)
{
    int aleft;

    aleft = ALEFT;
    hleft = HLEFT;
    do {
	if (--aleft == 0)
	    stderror(ERR_ALIASLOOP);
    } while (asyntax(lexp->next, lexp) != 0);
}