#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  aPrefix ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char quoteChar (char const*) ; 
 char* shellFakeSchema (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 char* sqlite3_mprintf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_stricmp (char const*,char*) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int strlen30 (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static void shellAddSchemaName(
  sqlite3_context *pCtx,
  int nVal,
  sqlite3_value **apVal
){
  static const char *aPrefix[] = {
     "TABLE",
     "INDEX",
     "UNIQUE INDEX",
     "VIEW",
     "TRIGGER",
     "VIRTUAL TABLE"
  };
  int i = 0;
  const char *zIn = (const char*)sqlite3_value_text(apVal[0]);
  const char *zSchema = (const char*)sqlite3_value_text(apVal[1]);
  const char *zName = (const char*)sqlite3_value_text(apVal[2]);
  sqlite3 *db = sqlite3_context_db_handle(pCtx);
  UNUSED_PARAMETER(nVal);
  if( zIn!=0 && strncmp(zIn, "CREATE ", 7)==0 ){
    for(i=0; i<(int)(sizeof(aPrefix)/sizeof(aPrefix[0])); i++){
      int n = strlen30(aPrefix[i]);
      if( strncmp(zIn+7, aPrefix[i], n)==0 && zIn[n+7]==' ' ){
        char *z = 0;
        char *zFake = 0;
        if( zSchema ){
          char cQuote = quoteChar(zSchema);
          if( cQuote && sqlite3_stricmp(zSchema,"temp")!=0 ){
            z = sqlite3_mprintf("%.*s \"%w\".%s", n+7, zIn, zSchema, zIn+n+8);
          }else{
            z = sqlite3_mprintf("%.*s %s.%s", n+7, zIn, zSchema, zIn+n+8);
          }
        }
        if( zName
         && aPrefix[i][0]=='V'
         && (zFake = shellFakeSchema(db, zSchema, zName))!=0
        ){
          if( z==0 ){
            z = sqlite3_mprintf("%s\n/* %s */", zIn, zFake);
          }else{
            z = sqlite3_mprintf("%z\n/* %s */", z, zFake);
          }
          free(zFake);
        }
        if( z ){
          sqlite3_result_text(pCtx, z, -1, sqlite3_free);
          return;
        }
      }
    }
  }
  sqlite3_result_value(pCtx, apVal[0]);
}