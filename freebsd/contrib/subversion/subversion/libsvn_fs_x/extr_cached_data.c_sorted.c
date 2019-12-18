#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_fs_x__dirent_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_5__ {int nelts; scalar_t__ elts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t
sorted(apr_array_header_t *entries)
{
  int i;

  const svn_fs_x__dirent_t * const *dirents = (const void *)entries->elts;
  for (i = 0; i < entries->nelts-1; ++i)
    if (strcmp(dirents[i]->name, dirents[i+1]->name) > 0)
      return FALSE;

  return TRUE;
}