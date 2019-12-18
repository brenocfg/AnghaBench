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
typedef  int /*<<< orphan*/  SHA3Context ;

/* Variables and functions */
 int /*<<< orphan*/  SHA3Final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA3Init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SHA3Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int SQLITE_BLOB ; 
 int SQLITE_NULL ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sha3Func(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  SHA3Context cx;
  int eType = sqlite3_value_type(argv[0]);
  int nByte = sqlite3_value_bytes(argv[0]);
  int iSize;
  if( argc==1 ){
    iSize = 256;
  }else{
    iSize = sqlite3_value_int(argv[1]);
    if( iSize!=224 && iSize!=256 && iSize!=384 && iSize!=512 ){
      sqlite3_result_error(context, "SHA3 size should be one of: 224 256 "
                                    "384 512", -1);
      return;
    }
  }
  if( eType==SQLITE_NULL ) return;
  SHA3Init(&cx, iSize);
  if( eType==SQLITE_BLOB ){
    SHA3Update(&cx, sqlite3_value_blob(argv[0]), nByte);
  }else{
    SHA3Update(&cx, sqlite3_value_text(argv[0]), nByte);
  }
  sqlite3_result_blob(context, SHA3Final(&cx), iSize/8, SQLITE_TRANSIENT);
}