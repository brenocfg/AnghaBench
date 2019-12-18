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
typedef  int svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  filter_exclude_date_author_sync (char const*) ; 

__attribute__((used)) static svn_boolean_t
filter_include_date_author_sync(const char *key)
{
  return ! filter_exclude_date_author_sync(key);
}