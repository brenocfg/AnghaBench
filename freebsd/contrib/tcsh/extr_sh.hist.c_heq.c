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
struct wordent {struct wordent* next; int /*<<< orphan*/  word; } ;

/* Variables and functions */
 scalar_t__ Strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
heq(const struct wordent *a0, const struct wordent *b0)
{
    const struct wordent *a = a0->next, *b = b0->next;

    for (;;) {
	if (Strcmp(a->word, b->word) != 0)
	    return 0;
	a = a->next;
	b = b->next;
	if (a == a0)
	    return (b == b0) ? 1 : 0;
	if (b == b0)
	    return 0;
    }
}