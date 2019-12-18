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
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 void SQLITE_DYNAMIC (void*) ; 
 int SQLITE_TOOBIG ; 
 void SQLITE_TRANSIENT (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_error_toobig (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int invokeValueDestructor(
  const void *p,             /* Value to destroy */
  void (*xDel)(void*),       /* The destructor */
  sqlite3_context *pCtx      /* Set a SQLITE_TOOBIG error if no NULL */
){
  assert( xDel!=SQLITE_DYNAMIC );
  if( xDel==0 ){
    /* noop */
  }else if( xDel==SQLITE_TRANSIENT ){
    /* noop */
  }else{
    xDel((void*)p);
  }
  if( pCtx ) sqlite3_result_error_toobig(pCtx);
  return SQLITE_TOOBIG;
}