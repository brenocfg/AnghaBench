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
typedef  scalar_t__ i64 ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int sqlite3_result_zeroblob64 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zeroblobFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  i64 n;
  int rc;
  assert( argc==1 );
  UNUSED_PARAMETER(argc);
  n = sqlite3_value_int64(argv[0]);
  if( n<0 ) n = 0;
  rc = sqlite3_result_zeroblob64(context, n); /* IMP: R-00293-64994 */
  if( rc ){
    sqlite3_result_error_code(context, rc);
  }
}