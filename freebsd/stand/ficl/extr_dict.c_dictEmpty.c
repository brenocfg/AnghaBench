#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * smudge; TYPE_1__* pForthWords; scalar_t__ here; scalar_t__ dict; } ;
struct TYPE_8__ {unsigned int size; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_HASH ;
typedef  TYPE_2__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  dictAlign (TYPE_2__*) ; 
 int /*<<< orphan*/  dictAllot (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dictResetSearchOrder (TYPE_2__*) ; 
 int /*<<< orphan*/  hashReset (TYPE_1__*) ; 

void dictEmpty(FICL_DICT *pDict, unsigned nHash)
{
    FICL_HASH *pHash;

    pDict->here = pDict->dict;

    dictAlign(pDict);
    pHash = (FICL_HASH *)pDict->here;
    dictAllot(pDict, 
              sizeof (FICL_HASH) + (nHash - 1) * sizeof (FICL_WORD *));

    pHash->size = nHash;
    hashReset(pHash);

    pDict->pForthWords = pHash;
    pDict->smudge = NULL;
    dictResetSearchOrder(pDict);
    return;
}