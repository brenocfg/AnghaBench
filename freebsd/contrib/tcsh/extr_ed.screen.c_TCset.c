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
struct termcapstr {int /*<<< orphan*/ * str; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xrealloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
TCset(struct termcapstr *t, const char *cap)
{
    if (cap == NULL || *cap == '\0') {
	xfree(t->str);
	t->str = NULL;
    } else {
	size_t size;

	size = strlen(cap) + 1;
	t->str = xrealloc(t->str, size);
	memcpy(t->str, cap, size);
    }
}