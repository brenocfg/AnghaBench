#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ action; scalar_t__ copyfrom_path; } ;
typedef  TYPE_1__ change_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ RESTRUCTURE_NONE ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
find_enclosing_copy(apr_hash_t *changes,
                    const char *relpath,
                    apr_pool_t *result_pool)
{
  while (*relpath)
    {
      const change_node_t *change = svn_hash_gets(changes, relpath);

      if (change)
        {
          if (change->copyfrom_path)
            return relpath;
          if (change->action != RESTRUCTURE_NONE)
            return NULL;
        }
      relpath = svn_relpath_dirname(relpath, result_pool);
    }

  return NULL;
}