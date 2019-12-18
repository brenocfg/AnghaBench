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
typedef  int /*<<< orphan*/  zHdr ;
typedef  int sqlite3_int64 ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_5__ {int (* xRead ) (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ memcmp (char*,char const*,int) ; 
 int stub1 (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apndIsOrdinaryDatabaseFile(sqlite3_int64 sz, sqlite3_file *pFile){
  int rc;
  char zHdr[16];
  static const char aSqliteHdr[] = "SQLite format 3";
  if( sz<512 ) return 0;
  rc = pFile->pMethods->xRead(pFile, zHdr, sizeof(zHdr), 0);
  if( rc ) return 0;
  return memcmp(zHdr, aSqliteHdr, sizeof(zHdr))==0;
}