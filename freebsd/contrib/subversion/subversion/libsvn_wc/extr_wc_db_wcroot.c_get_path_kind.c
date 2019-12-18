#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kind; TYPE_3__* abspath; } ;
struct TYPE_7__ {TYPE_1__ parse_cache; int /*<<< orphan*/  state_pool; } ;
typedef  TYPE_2__ svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_symlink ; 
 TYPE_3__* svn_stringbuf_create (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_set (TYPE_3__*,char const*) ; 

__attribute__((used)) static svn_error_t *
get_path_kind(svn_node_kind_t *kind,
              svn_wc__db_t *db,
              const char *local_abspath,
              apr_pool_t *scratch_pool)
{
  svn_boolean_t special;
  svn_node_kind_t node_kind;

  /* This implements a *really* simple LRU cache, where "simple" is defined
     as "only one element".  In other words, we remember the most recently
     queried path, and nothing else.  This gives >80% cache hits. */

  if (db->parse_cache.abspath
        && strcmp(db->parse_cache.abspath->data, local_abspath) == 0)
    {
      /* Cache hit! */
      *kind = db->parse_cache.kind;
      return SVN_NO_ERROR;
    }

  if (!db->parse_cache.abspath)
    {
      db->parse_cache.abspath = svn_stringbuf_create(local_abspath,
                                                     db->state_pool);
    }
  else
    {
      svn_stringbuf_set(db->parse_cache.abspath, local_abspath);
    }

  SVN_ERR(svn_io_check_special_path(local_abspath, &node_kind,
                                    &special, scratch_pool));

  db->parse_cache.kind = (special ? svn_node_symlink : node_kind);
  *kind = db->parse_cache.kind;

  return SVN_NO_ERROR;
}