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
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void row_numberStepFunc(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **apArg
){
  i64 *p = (i64*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p ) (*p)++;
  UNUSED_PARAMETER(nArg);
  UNUSED_PARAMETER(apArg);
}