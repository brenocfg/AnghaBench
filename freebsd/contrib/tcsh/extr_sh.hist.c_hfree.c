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
struct Hist {struct Hist* histline; int /*<<< orphan*/  Hlex; scalar_t__ Hhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freelex (int /*<<< orphan*/ *) ; 
 struct Hist* histMerg ; 
 int /*<<< orphan*/  removeHistHashTable (struct Hist*) ; 
 int /*<<< orphan*/  xfree (struct Hist*) ; 

__attribute__((used)) static void
hfree(struct Hist *hp)
{
    assert(hp != histMerg);
    if (hp->Hhash)
        removeHistHashTable(hp);
    freelex(&hp->Hlex);
    if (hp->histline)
        xfree(hp->histline);
    xfree(hp);
}