#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ xMalloc; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_CONFIG_GETMALLOC ; 
 int /*<<< orphan*/  SQLITE_CONFIG_MALLOC ; 
 int SQLITE_OK ; 
 TYPE_1__ ersaztMethods ; 
 TYPE_1__ memtraceBase ; 
 int /*<<< orphan*/ * memtraceOut ; 
 int sqlite3_config (int /*<<< orphan*/ ,TYPE_1__*) ; 

int sqlite3MemTraceActivate(FILE *out){
  int rc = SQLITE_OK;
  if( memtraceBase.xMalloc==0 ){
    rc = sqlite3_config(SQLITE_CONFIG_GETMALLOC, &memtraceBase);
    if( rc==SQLITE_OK ){
      rc = sqlite3_config(SQLITE_CONFIG_MALLOC, &ersaztMethods);
    }
  }
  memtraceOut = out;
  return rc;
}