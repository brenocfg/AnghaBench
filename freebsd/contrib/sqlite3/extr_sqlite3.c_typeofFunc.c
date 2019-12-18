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

/* Variables and functions */
 int ArraySize (char const**) ; 
 int SQLITE_BLOB ; 
 int SQLITE_FLOAT ; 
 int SQLITE_INTEGER ; 
 int SQLITE_NULL ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int SQLITE_TEXT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void typeofFunc(
  sqlite3_context *context,
  int NotUsed,
  sqlite3_value **argv
){
  static const char *azType[] = { "integer", "real", "text", "blob", "null" };
  int i = sqlite3_value_type(argv[0]) - 1;
  UNUSED_PARAMETER(NotUsed);
  assert( i>=0 && i<ArraySize(azType) );
  assert( SQLITE_INTEGER==1 );
  assert( SQLITE_FLOAT==2 );
  assert( SQLITE_TEXT==3 );
  assert( SQLITE_BLOB==4 );
  assert( SQLITE_NULL==5 );
  /* EVIDENCE-OF: R-01470-60482 The sqlite3_value_type(V) interface returns
  ** the datatype code for the initial datatype of the sqlite3_value object
  ** V. The returned value is one of SQLITE_INTEGER, SQLITE_FLOAT,
  ** SQLITE_TEXT, SQLITE_BLOB, or SQLITE_NULL. */
  sqlite3_result_text(context, azType[i], -1, SQLITE_STATIC);
}