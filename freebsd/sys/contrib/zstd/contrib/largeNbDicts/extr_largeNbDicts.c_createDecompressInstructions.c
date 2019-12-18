#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nbDDict; } ;
struct TYPE_5__ {TYPE_2__ dictionaries; scalar_t__ dictNb; int /*<<< orphan*/  nbDicts; int /*<<< orphan*/ * dctx; } ;
typedef  TYPE_1__ decompressInstructions ;
typedef  TYPE_2__ ddict_collection_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

decompressInstructions createDecompressInstructions(ddict_collection_t dictionaries)
{
    decompressInstructions di;
    di.dctx = ZSTD_createDCtx();
    assert(di.dctx != NULL);
    di.nbDicts = dictionaries.nbDDict;
    di.dictNb = 0;
    di.dictionaries = dictionaries;
    return di;
}