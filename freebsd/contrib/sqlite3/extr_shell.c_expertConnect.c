#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pTable; } ;
typedef  TYPE_2__ sqlite3expert ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {TYPE_1__* pTab; TYPE_2__* pExpert; } ;
struct TYPE_5__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_3__ ExpertVtab ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 char* expertDequote (char const* const) ; 
 TYPE_3__* idxMalloc (int*,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*) ; 
 scalar_t__ sqlite3_stricmp (int /*<<< orphan*/ ,char const* const) ; 

__attribute__((used)) static int expertConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  sqlite3expert *pExpert = (sqlite3expert*)pAux;
  ExpertVtab *p = 0;
  int rc;

  if( argc!=4 ){
    *pzErr = sqlite3_mprintf("internal error!");
    rc = SQLITE_ERROR;
  }else{
    char *zCreateTable = expertDequote(argv[3]);
    if( zCreateTable ){
      rc = sqlite3_declare_vtab(db, zCreateTable);
      if( rc==SQLITE_OK ){
        p = idxMalloc(&rc, sizeof(ExpertVtab));
      }
      if( rc==SQLITE_OK ){
        p->pExpert = pExpert;
        p->pTab = pExpert->pTable;
        assert( sqlite3_stricmp(p->pTab->zName, argv[2])==0 );
      }
      sqlite3_free(zCreateTable);
    }else{
      rc = SQLITE_NOMEM;
    }
  }

  *ppVtab = (sqlite3_vtab*)p;
  return rc;
}