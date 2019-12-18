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
 int /*<<< orphan*/  savedSelectTrace ; 
 int /*<<< orphan*/  savedWhereTrace ; 
 int /*<<< orphan*/  sqlite3SelectTrace ; 
 int /*<<< orphan*/  sqlite3WhereTrace ; 

__attribute__((used)) static void restore_debug_trace_modes(void){
#if defined(SQLITE_DEBUG) && defined(SQLITE_ENABLE_SELECTTRACE)
  sqlite3SelectTrace = savedSelectTrace;
#endif
#if defined(SQLITE_DEBUG) && defined(SQLITE_ENABLE_WHERETRACE)
  sqlite3WhereTrace = savedWhereTrace;
#endif
}