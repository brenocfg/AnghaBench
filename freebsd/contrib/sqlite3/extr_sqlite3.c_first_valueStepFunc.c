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
struct NthValueCtx {scalar_t__ pValue; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_dup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void first_valueStepFunc(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **apArg
){
  struct NthValueCtx *p;
  p = (struct NthValueCtx*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p && p->pValue==0 ){
    p->pValue = sqlite3_value_dup(apArg[0]);
    if( !p->pValue ){
      sqlite3_result_error_nomem(pCtx);
    }
  }
  UNUSED_PARAMETER(nArg);
  UNUSED_PARAMETER(apArg);
}