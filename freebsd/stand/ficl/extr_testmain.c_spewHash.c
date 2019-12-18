#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* pForthWords; } ;
struct TYPE_12__ {unsigned int size; TYPE_1__** table; } ;
struct TYPE_11__ {int /*<<< orphan*/  pad; } ;
struct TYPE_10__ {char* name; struct TYPE_10__* link; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;
typedef  TYPE_3__ FICL_HASH ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OUTOFTEXT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_7__* vmGetDict (TYPE_2__*) ; 
 int /*<<< orphan*/  vmGetWordToPad (TYPE_2__*) ; 
 int /*<<< orphan*/  vmTextOut (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  vmThrow (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spewHash(FICL_VM *pVM)
{
    FICL_HASH *pHash = vmGetDict(pVM)->pForthWords;
    FICL_WORD *pFW;
    FILE *pOut;
    unsigned i;
    unsigned nHash = pHash->size;

    if (!vmGetWordToPad(pVM))
        vmThrow(pVM, VM_OUTOFTEXT);

    pOut = fopen(pVM->pad, "w");
    if (!pOut)
    {
        vmTextOut(pVM, "unable to open file", 1);
        return;
    }

    for (i=0; i < nHash; i++)
    {
        int n = 0;

        pFW = pHash->table[i];
        while (pFW)
        {
            n++;
            pFW = pFW->link;
        }

        fprintf(pOut, "%d\t%d", i, n);

        pFW = pHash->table[i];
        while (pFW)
        {
            fprintf(pOut, "\t%s", pFW->name);
            pFW = pFW->link;
        }

        fprintf(pOut, "\n");
    }

    fclose(pOut);
    return;
}