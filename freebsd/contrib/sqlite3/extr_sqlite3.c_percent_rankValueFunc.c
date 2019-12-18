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
struct CallCount {int nTotal; scalar_t__ nValue; scalar_t__ nStep; } ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static void percent_rankValueFunc(sqlite3_context *pCtx){
  struct CallCount *p;
  p = (struct CallCount*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p ){
    p->nValue = p->nStep;
    if( p->nTotal>1 ){
      double r = (double)p->nValue / (double)(p->nTotal-1);
      sqlite3_result_double(pCtx, r);
    }else{
      sqlite3_result_double(pCtx, 0.0);
    }
  }
}