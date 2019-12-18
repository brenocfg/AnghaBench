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

/* Variables and functions */
 scalar_t__ savedSelectTrace ; 
 scalar_t__ savedWhereTrace ; 
 scalar_t__ sqlite3SelectTrace ; 
 scalar_t__ sqlite3WhereTrace ; 

__attribute__((used)) static void disable_debug_trace_modes(void){
#if defined(SQLITE_DEBUG) && defined(SQLITE_ENABLE_SELECTTRACE)
  savedSelectTrace = sqlite3SelectTrace;
  sqlite3SelectTrace = 0;
#endif
#if defined(SQLITE_DEBUG) && defined(SQLITE_ENABLE_WHERETRACE)
  savedWhereTrace = sqlite3WhereTrace;
  sqlite3WhereTrace = 0;
#endif
}