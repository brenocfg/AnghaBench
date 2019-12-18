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
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shellIdQuote(
  sqlite3_context *context, 
  int argc, 
  sqlite3_value **argv
){
  const char *zName = (const char*)sqlite3_value_text(argv[0]);
  UNUSED_PARAMETER(argc);
  if( zName ){
    char *z = sqlite3_mprintf("\"%w\"", zName);
    sqlite3_result_text(context, z, -1, sqlite3_free);
  }
}