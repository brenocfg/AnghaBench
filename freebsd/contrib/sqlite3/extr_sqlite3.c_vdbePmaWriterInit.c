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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int i64 ;
struct TYPE_4__ {int iBufEnd; int iBufStart; int iWriteOff; int nBuffer; int /*<<< orphan*/ * pFd; int /*<<< orphan*/  eFWErr; int /*<<< orphan*/ * aBuffer; } ;
typedef  TYPE_1__ PmaWriter ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_NOMEM_BKPT ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Malloc (int) ; 

__attribute__((used)) static void vdbePmaWriterInit(
  sqlite3_file *pFd,              /* File handle to write to */
  PmaWriter *p,                   /* Object to populate */
  int nBuf,                       /* Buffer size */
  i64 iStart                      /* Offset of pFd to begin writing at */
){
  memset(p, 0, sizeof(PmaWriter));
  p->aBuffer = (u8*)sqlite3Malloc(nBuf);
  if( !p->aBuffer ){
    p->eFWErr = SQLITE_NOMEM_BKPT;
  }else{
    p->iBufEnd = p->iBufStart = (iStart % nBuf);
    p->iWriteOff = iStart - p->iBufStart;
    p->nBuffer = nBuf;
    p->pFd = pFd;
  }
}