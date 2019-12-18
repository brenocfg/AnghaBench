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
struct wordent {struct wordent* next; int /*<<< orphan*/ * word; } ;
struct command {int dummy; } ;

/* Variables and functions */
 scalar_t__ any (char*,int /*<<< orphan*/ ) ; 
 struct command* syn0 (struct wordent const*,struct wordent const*,int) ; 

struct command *
syntax(const struct wordent *p1, const struct wordent *p2, int flags)
{

    while (p1 != p2)
	if (any(";&\n", p1->word[0]))
	    p1 = p1->next;
	else
	    return (syn0(p1, p2, flags));
    return (0);
}