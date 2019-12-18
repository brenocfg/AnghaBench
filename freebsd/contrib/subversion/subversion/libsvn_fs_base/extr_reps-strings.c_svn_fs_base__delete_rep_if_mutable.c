#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  string_key; } ;
struct TYPE_7__ {TYPE_2__ fulltext; } ;
struct TYPE_9__ {scalar_t__ kind; TYPE_1__ contents; } ;
typedef  TYPE_3__ representation_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * UNKNOWN_NODE_KIND (char const*) ; 
 int /*<<< orphan*/  delete_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_string_keys (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rep_is_mutable (TYPE_3__*,char const*) ; 
 scalar_t__ rep_kind_delta ; 
 scalar_t__ rep_kind_fulltext ; 
 int /*<<< orphan*/ * svn_fs_bdb__delete_rep (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__read_rep (TYPE_3__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__string_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__delete_rep_if_mutable(svn_fs_t *fs,
                                   const char *rep_key,
                                   const char *txn_id,
                                   trail_t *trail,
                                   apr_pool_t *pool)
{
  representation_t *rep;

  SVN_ERR(svn_fs_bdb__read_rep(&rep, fs, rep_key, trail, pool));
  if (! rep_is_mutable(rep, txn_id))
    return SVN_NO_ERROR;

  if (rep->kind == rep_kind_fulltext)
    {
      SVN_ERR(svn_fs_bdb__string_delete(fs,
                                        rep->contents.fulltext.string_key,
                                        trail, pool));
    }
  else if (rep->kind == rep_kind_delta)
    {
      apr_array_header_t *keys;
      SVN_ERR(delta_string_keys(&keys, rep, pool));
      SVN_ERR(delete_strings(keys, fs, trail, pool));
    }
  else /* unknown kind */
    return UNKNOWN_NODE_KIND(rep_key);

  return svn_fs_bdb__delete_rep(fs, rep_key, trail, pool);
}