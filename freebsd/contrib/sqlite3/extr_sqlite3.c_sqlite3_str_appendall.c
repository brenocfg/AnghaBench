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
typedef  int /*<<< orphan*/  sqlite3_str ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3_str_append (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void sqlite3_str_appendall(sqlite3_str *p, const char *z){
  sqlite3_str_append(p, z, sqlite3Strlen30(z));
}