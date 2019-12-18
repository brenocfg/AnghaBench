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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ Islower (int /*<<< orphan*/ ) ; 
 scalar_t__ Isupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Tolower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Toupper (int /*<<< orphan*/ ) ; 

Char *
NLSChangeCase(const Char *p, int mode)
{
    Char c, *n, c2 = 0;
    const Char *op = p;

    for (; (c = *p) != 0; p++) {
        if (mode == 0 && Islower(c)) {
	    c2 = Toupper(c);
	    break;
        } else if (mode && Isupper(c)) {
	    c2 = Tolower(c);
	    break;
	}
    }
    if (!*p)
	return 0;
    n = Strsave(op);
    n[p - op] = c2;
    return n;
}