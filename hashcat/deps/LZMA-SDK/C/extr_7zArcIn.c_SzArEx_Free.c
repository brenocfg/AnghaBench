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
struct TYPE_4__ {int /*<<< orphan*/  db; int /*<<< orphan*/  CTime; int /*<<< orphan*/  MTime; int /*<<< orphan*/  Attribs; int /*<<< orphan*/  CRCs; int /*<<< orphan*/  FileNames; int /*<<< orphan*/  FileNameOffsets; int /*<<< orphan*/  FileToFolder; int /*<<< orphan*/  FolderToFile; int /*<<< orphan*/  IsDirs; int /*<<< orphan*/  UnpackPositions; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CSzArEx ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SzArEx_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  SzAr_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SzBitUi32s_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SzBitUi64s_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SzArEx_Free(CSzArEx *p, ISzAllocPtr alloc)
{
  ISzAlloc_Free(alloc, p->UnpackPositions);
  ISzAlloc_Free(alloc, p->IsDirs);

  ISzAlloc_Free(alloc, p->FolderToFile);
  ISzAlloc_Free(alloc, p->FileToFolder);

  ISzAlloc_Free(alloc, p->FileNameOffsets);
  ISzAlloc_Free(alloc, p->FileNames);

  SzBitUi32s_Free(&p->CRCs, alloc);
  SzBitUi32s_Free(&p->Attribs, alloc);
  // SzBitUi32s_Free(&p->Parents, alloc);
  SzBitUi64s_Free(&p->MTime, alloc);
  SzBitUi64s_Free(&p->CTime, alloc);
  
  SzAr_Free(&p->db, alloc);
  SzArEx_Init(p);
}