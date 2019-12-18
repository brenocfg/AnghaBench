#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * CodersData; int /*<<< orphan*/ * CoderUnpackSizes; int /*<<< orphan*/ * FoToMainUnpackSizeIndex; int /*<<< orphan*/ * FoToCoderUnpackSizes; int /*<<< orphan*/ * FoStartPackStreamIndex; int /*<<< orphan*/ * FoCodersOffsets; int /*<<< orphan*/  FolderCRCs; int /*<<< orphan*/ * PackPositions; scalar_t__ NumFolders; scalar_t__ NumPackStreams; } ;
typedef  TYPE_1__ CSzAr ;

/* Variables and functions */
 int /*<<< orphan*/  SzBitUi32s_Init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SzAr_Init(CSzAr *p)
{
  p->NumPackStreams = 0;
  p->NumFolders = 0;
  
  p->PackPositions = NULL;
  SzBitUi32s_Init(&p->FolderCRCs);

  p->FoCodersOffsets = NULL;
  p->FoStartPackStreamIndex = NULL;
  p->FoToCoderUnpackSizes = NULL;
  p->FoToMainUnpackSizeIndex = NULL;
  p->CoderUnpackSizes = NULL;

  p->CodersData = NULL;
}