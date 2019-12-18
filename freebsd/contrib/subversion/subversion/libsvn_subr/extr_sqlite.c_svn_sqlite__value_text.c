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
typedef  int /*<<< orphan*/  svn_sqlite__value_t ;

/* Variables and functions */
 scalar_t__ sqlite3_value_text (void*) ; 

const char *
svn_sqlite__value_text(svn_sqlite__value_t *val)
{
  void *v = val;
  return (const char *) sqlite3_value_text(v);
}