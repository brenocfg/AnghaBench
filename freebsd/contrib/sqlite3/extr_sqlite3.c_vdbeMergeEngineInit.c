#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nTree; int /*<<< orphan*/ * aReadr; TYPE_2__* pTask; } ;
struct TYPE_8__ {TYPE_1__* pUnpacked; } ;
struct TYPE_7__ {int errCode; } ;
typedef  TYPE_2__ SortSubtask ;
typedef  TYPE_3__ MergeEngine ;

/* Variables and functions */
 int INCRINIT_NORMAL ; 
 int INCRINIT_ROOT ; 
 scalar_t__ SQLITE_MAX_WORKER_THREADS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vdbeMergeEngineCompare (TYPE_3__*,int) ; 
 int vdbePmaReaderIncrInit (int /*<<< orphan*/ *,int) ; 
 int vdbePmaReaderNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdbeMergeEngineInit(
  SortSubtask *pTask,             /* Thread that will run pMerger */
  MergeEngine *pMerger,           /* MergeEngine to initialize */
  int eMode                       /* One of the INCRINIT_XXX constants */
){
  int rc = SQLITE_OK;             /* Return code */
  int i;                          /* For looping over PmaReader objects */
  int nTree;                      /* Number of subtrees to merge */

  /* Failure to allocate the merge would have been detected prior to
  ** invoking this routine */
  assert( pMerger!=0 );

  /* eMode is always INCRINIT_NORMAL in single-threaded mode */
  assert( SQLITE_MAX_WORKER_THREADS>0 || eMode==INCRINIT_NORMAL );

  /* Verify that the MergeEngine is assigned to a single thread */
  assert( pMerger->pTask==0 );
  pMerger->pTask = pTask;

  nTree = pMerger->nTree;
  for(i=0; i<nTree; i++){
    if( SQLITE_MAX_WORKER_THREADS>0 && eMode==INCRINIT_ROOT ){
      /* PmaReaders should be normally initialized in order, as if they are
      ** reading from the same temp file this makes for more linear file IO.
      ** However, in the INCRINIT_ROOT case, if PmaReader aReadr[nTask-1] is
      ** in use it will block the vdbePmaReaderNext() call while it uses
      ** the main thread to fill its buffer. So calling PmaReaderNext()
      ** on this PmaReader before any of the multi-threaded PmaReaders takes
      ** better advantage of multi-processor hardware. */
      rc = vdbePmaReaderNext(&pMerger->aReadr[nTree-i-1]);
    }else{
      rc = vdbePmaReaderIncrInit(&pMerger->aReadr[i], INCRINIT_NORMAL);
    }
    if( rc!=SQLITE_OK ) return rc;
  }

  for(i=pMerger->nTree-1; i>0; i--){
    vdbeMergeEngineCompare(pMerger, i);
  }
  return pTask->pUnpacked->errCode;
}