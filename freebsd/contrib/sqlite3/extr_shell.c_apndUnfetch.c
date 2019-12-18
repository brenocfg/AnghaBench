#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_9__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_10__ {scalar_t__ iPgOne; } ;
struct TYPE_8__ {int (* xUnfetch ) (TYPE_2__*,scalar_t__,void*) ;} ;
typedef  TYPE_3__ ApndFile ;

/* Variables and functions */
 TYPE_2__* ORIGFILE (TYPE_2__*) ; 
 int stub1 (TYPE_2__*,scalar_t__,void*) ; 

__attribute__((used)) static int apndUnfetch(sqlite3_file *pFile, sqlite3_int64 iOfst, void *pPage){
  ApndFile *p = (ApndFile *)pFile;
  pFile = ORIGFILE(pFile);
  return pFile->pMethods->xUnfetch(pFile, iOfst+p->iPgOne, pPage);
}