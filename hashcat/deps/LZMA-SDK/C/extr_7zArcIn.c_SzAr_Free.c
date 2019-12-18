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
struct TYPE_4__ {int /*<<< orphan*/  CodersData; int /*<<< orphan*/  CoderUnpackSizes; int /*<<< orphan*/  FoToMainUnpackSizeIndex; int /*<<< orphan*/  FoToCoderUnpackSizes; int /*<<< orphan*/  FoStartPackStreamIndex; int /*<<< orphan*/  FoCodersOffsets; int /*<<< orphan*/  FolderCRCs; int /*<<< orphan*/  PackPositions; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CSzAr ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SzAr_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  SzBitUi32s_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SzAr_Free(CSzAr *p, ISzAllocPtr alloc)
{
  ISzAlloc_Free(alloc, p->PackPositions);
  SzBitUi32s_Free(&p->FolderCRCs, alloc);
 
  ISzAlloc_Free(alloc, p->FoCodersOffsets);
  ISzAlloc_Free(alloc, p->FoStartPackStreamIndex);
  ISzAlloc_Free(alloc, p->FoToCoderUnpackSizes);
  ISzAlloc_Free(alloc, p->FoToMainUnpackSizeIndex);
  ISzAlloc_Free(alloc, p->CoderUnpackSizes);
  
  ISzAlloc_Free(alloc, p->CodersData);

  SzAr_Init(p);
}