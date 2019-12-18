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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shellInt32(
  sqlite3_context *context, 
  int argc, 
  sqlite3_value **argv
){
  const unsigned char *pBlob;
  int nBlob;
  int iInt;

  UNUSED_PARAMETER(argc);
  nBlob = sqlite3_value_bytes(argv[0]);
  pBlob = (const unsigned char*)sqlite3_value_blob(argv[0]);
  iInt = sqlite3_value_int(argv[1]);

  if( iInt>=0 && (iInt+1)*4<=nBlob ){
    const unsigned char *a = &pBlob[iInt*4];
    sqlite3_int64 iVal = ((sqlite3_int64)a[0]<<24)
                       + ((sqlite3_int64)a[1]<<16)
                       + ((sqlite3_int64)a[2]<< 8)
                       + ((sqlite3_int64)a[3]<< 0);
    sqlite3_result_int64(context, iVal);
  }
}