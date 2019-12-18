#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ stype; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
 scalar_t__ SUndefined ; 
 int /*<<< orphan*/  lex_error_message (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
checkfunc(void *ptr, void *arg)
{
    Symbol *s = ptr;
    if (s->stype == SUndefined) {
	lex_error_message("%s is still undefined\n", s->name);
	*(int *) arg = 1;
    }
    return 0;
}