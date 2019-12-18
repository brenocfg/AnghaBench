#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tcl_DString ;
struct TYPE_2__ {int /*<<< orphan*/  interp; int /*<<< orphan*/  zAuth; scalar_t__ disableAuth; } ;
typedef  TYPE_1__ SqliteDb ;

/* Variables and functions */
#define  SQLITE_ALTER_TABLE 161 
#define  SQLITE_ANALYZE 160 
#define  SQLITE_ATTACH 159 
#define  SQLITE_COPY 158 
#define  SQLITE_CREATE_INDEX 157 
#define  SQLITE_CREATE_TABLE 156 
#define  SQLITE_CREATE_TEMP_INDEX 155 
#define  SQLITE_CREATE_TEMP_TABLE 154 
#define  SQLITE_CREATE_TEMP_TRIGGER 153 
#define  SQLITE_CREATE_TEMP_VIEW 152 
#define  SQLITE_CREATE_TRIGGER 151 
#define  SQLITE_CREATE_VIEW 150 
#define  SQLITE_CREATE_VTABLE 149 
#define  SQLITE_DELETE 148 
 int SQLITE_DENY ; 
#define  SQLITE_DETACH 147 
#define  SQLITE_DROP_INDEX 146 
#define  SQLITE_DROP_TABLE 145 
#define  SQLITE_DROP_TEMP_INDEX 144 
#define  SQLITE_DROP_TEMP_TABLE 143 
#define  SQLITE_DROP_TEMP_TRIGGER 142 
#define  SQLITE_DROP_TEMP_VIEW 141 
#define  SQLITE_DROP_TRIGGER 140 
#define  SQLITE_DROP_VIEW 139 
#define  SQLITE_DROP_VTABLE 138 
#define  SQLITE_FUNCTION 137 
 int SQLITE_IGNORE ; 
#define  SQLITE_INSERT 136 
 int SQLITE_OK ; 
#define  SQLITE_PRAGMA 135 
#define  SQLITE_READ 134 
#define  SQLITE_RECURSIVE 133 
#define  SQLITE_REINDEX 132 
#define  SQLITE_SAVEPOINT 131 
#define  SQLITE_SELECT 130 
#define  SQLITE_TRANSACTION 129 
#define  SQLITE_UPDATE 128 
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_DStringAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Tcl_DStringAppendElement (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  Tcl_DStringFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_DStringInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_DStringValue (int /*<<< orphan*/ *) ; 
 char* Tcl_GetStringResult (int /*<<< orphan*/ ) ; 
 int Tcl_GlobalEval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int auth_callback(
  void *pArg,
  int code,
  const char *zArg1,
  const char *zArg2,
  const char *zArg3,
  const char *zArg4
#ifdef SQLITE_USER_AUTHENTICATION
  ,const char *zArg5
#endif
){
  const char *zCode;
  Tcl_DString str;
  int rc;
  const char *zReply;
  /* EVIDENCE-OF: R-38590-62769 The first parameter to the authorizer
  ** callback is a copy of the third parameter to the
  ** sqlite3_set_authorizer() interface.
  */
  SqliteDb *pDb = (SqliteDb*)pArg;
  if( pDb->disableAuth ) return SQLITE_OK;

  /* EVIDENCE-OF: R-56518-44310 The second parameter to the callback is an
  ** integer action code that specifies the particular action to be
  ** authorized. */
  switch( code ){
    case SQLITE_COPY              : zCode="SQLITE_COPY"; break;
    case SQLITE_CREATE_INDEX      : zCode="SQLITE_CREATE_INDEX"; break;
    case SQLITE_CREATE_TABLE      : zCode="SQLITE_CREATE_TABLE"; break;
    case SQLITE_CREATE_TEMP_INDEX : zCode="SQLITE_CREATE_TEMP_INDEX"; break;
    case SQLITE_CREATE_TEMP_TABLE : zCode="SQLITE_CREATE_TEMP_TABLE"; break;
    case SQLITE_CREATE_TEMP_TRIGGER: zCode="SQLITE_CREATE_TEMP_TRIGGER"; break;
    case SQLITE_CREATE_TEMP_VIEW  : zCode="SQLITE_CREATE_TEMP_VIEW"; break;
    case SQLITE_CREATE_TRIGGER    : zCode="SQLITE_CREATE_TRIGGER"; break;
    case SQLITE_CREATE_VIEW       : zCode="SQLITE_CREATE_VIEW"; break;
    case SQLITE_DELETE            : zCode="SQLITE_DELETE"; break;
    case SQLITE_DROP_INDEX        : zCode="SQLITE_DROP_INDEX"; break;
    case SQLITE_DROP_TABLE        : zCode="SQLITE_DROP_TABLE"; break;
    case SQLITE_DROP_TEMP_INDEX   : zCode="SQLITE_DROP_TEMP_INDEX"; break;
    case SQLITE_DROP_TEMP_TABLE   : zCode="SQLITE_DROP_TEMP_TABLE"; break;
    case SQLITE_DROP_TEMP_TRIGGER : zCode="SQLITE_DROP_TEMP_TRIGGER"; break;
    case SQLITE_DROP_TEMP_VIEW    : zCode="SQLITE_DROP_TEMP_VIEW"; break;
    case SQLITE_DROP_TRIGGER      : zCode="SQLITE_DROP_TRIGGER"; break;
    case SQLITE_DROP_VIEW         : zCode="SQLITE_DROP_VIEW"; break;
    case SQLITE_INSERT            : zCode="SQLITE_INSERT"; break;
    case SQLITE_PRAGMA            : zCode="SQLITE_PRAGMA"; break;
    case SQLITE_READ              : zCode="SQLITE_READ"; break;
    case SQLITE_SELECT            : zCode="SQLITE_SELECT"; break;
    case SQLITE_TRANSACTION       : zCode="SQLITE_TRANSACTION"; break;
    case SQLITE_UPDATE            : zCode="SQLITE_UPDATE"; break;
    case SQLITE_ATTACH            : zCode="SQLITE_ATTACH"; break;
    case SQLITE_DETACH            : zCode="SQLITE_DETACH"; break;
    case SQLITE_ALTER_TABLE       : zCode="SQLITE_ALTER_TABLE"; break;
    case SQLITE_REINDEX           : zCode="SQLITE_REINDEX"; break;
    case SQLITE_ANALYZE           : zCode="SQLITE_ANALYZE"; break;
    case SQLITE_CREATE_VTABLE     : zCode="SQLITE_CREATE_VTABLE"; break;
    case SQLITE_DROP_VTABLE       : zCode="SQLITE_DROP_VTABLE"; break;
    case SQLITE_FUNCTION          : zCode="SQLITE_FUNCTION"; break;
    case SQLITE_SAVEPOINT         : zCode="SQLITE_SAVEPOINT"; break;
    case SQLITE_RECURSIVE         : zCode="SQLITE_RECURSIVE"; break;
    default                       : zCode="????"; break;
  }
  Tcl_DStringInit(&str);
  Tcl_DStringAppend(&str, pDb->zAuth, -1);
  Tcl_DStringAppendElement(&str, zCode);
  Tcl_DStringAppendElement(&str, zArg1 ? zArg1 : "");
  Tcl_DStringAppendElement(&str, zArg2 ? zArg2 : "");
  Tcl_DStringAppendElement(&str, zArg3 ? zArg3 : "");
  Tcl_DStringAppendElement(&str, zArg4 ? zArg4 : "");
#ifdef SQLITE_USER_AUTHENTICATION
  Tcl_DStringAppendElement(&str, zArg5 ? zArg5 : "");
#endif
  rc = Tcl_GlobalEval(pDb->interp, Tcl_DStringValue(&str));
  Tcl_DStringFree(&str);
  zReply = rc==TCL_OK ? Tcl_GetStringResult(pDb->interp) : "SQLITE_DENY";
  if( strcmp(zReply,"SQLITE_OK")==0 ){
    rc = SQLITE_OK;
  }else if( strcmp(zReply,"SQLITE_DENY")==0 ){
    rc = SQLITE_DENY;
  }else if( strcmp(zReply,"SQLITE_IGNORE")==0 ){
    rc = SQLITE_IGNORE;
  }else{
    rc = 999;
  }
  return rc;
}