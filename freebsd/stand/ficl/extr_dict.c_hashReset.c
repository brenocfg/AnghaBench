#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int size; int /*<<< orphan*/ * name; int /*<<< orphan*/ * link; int /*<<< orphan*/ ** table; } ;
typedef  TYPE_1__ FICL_HASH ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void hashReset(FICL_HASH *pHash)
{
    unsigned i;

    assert(pHash);

    for (i = 0; i < pHash->size; i++)
    {
        pHash->table[i] = NULL;
    }

    pHash->link = NULL;
    pHash->name = NULL;
    return;
}