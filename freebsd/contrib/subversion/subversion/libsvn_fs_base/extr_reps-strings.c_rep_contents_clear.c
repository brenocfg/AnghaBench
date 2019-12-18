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
struct TYPE_7__ {char* string_key; } ;
struct TYPE_8__ {TYPE_1__ fulltext; } ;
struct TYPE_9__ {scalar_t__ kind; int /*<<< orphan*/ * sha1_checksum; int /*<<< orphan*/ * md5_checksum; TYPE_2__ contents; } ;
typedef  TYPE_3__ representation_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_REP_NOT_MUTABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  rep_is_mutable (TYPE_3__*,char const*) ; 
 scalar_t__ rep_kind_fulltext ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_bdb__read_rep (TYPE_3__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__string_clear (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__write_rep (int /*<<< orphan*/ *,char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rep_contents_clear(svn_fs_t *fs,
                   const char *rep_key,
                   const char *txn_id,
                   trail_t *trail,
                   apr_pool_t *pool)
{
  representation_t *rep;
  const char *str_key;

  SVN_ERR(svn_fs_bdb__read_rep(&rep, fs, rep_key, trail, pool));

  /* Make sure it's mutable. */
  if (! rep_is_mutable(rep, txn_id))
    return svn_error_createf
      (SVN_ERR_FS_REP_NOT_MUTABLE, NULL,
       _("Rep '%s' is not mutable"), rep_key);

  SVN_ERR_ASSERT(rep->kind == rep_kind_fulltext);

  /* If rep has no string, just return success.  Else, clear the
     underlying string.  */
  str_key = rep->contents.fulltext.string_key;
  if (str_key && *str_key)
    {
      SVN_ERR(svn_fs_bdb__string_clear(fs, str_key, trail, pool));
      rep->md5_checksum = NULL;
      rep->sha1_checksum = NULL;
      SVN_ERR(svn_fs_bdb__write_rep(fs, rep_key, rep, trail, pool));
    }
  return SVN_NO_ERROR;
}