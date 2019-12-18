#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_14__ {int /*<<< orphan*/  change_set; void* number; } ;
struct TYPE_15__ {TYPE_1__ id; void* expanded_size; void* size; int /*<<< orphan*/  has_sha1; int /*<<< orphan*/  sha1_digest; } ;
typedef  TYPE_2__ svn_fs_x__representation_t ;
struct TYPE_16__ {int /*<<< orphan*/  rep_cache_db; int /*<<< orphan*/  rep_sharing_allowed; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
struct TYPE_17__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_4__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_18__ {scalar_t__ kind; int /*<<< orphan*/  digest; } ;
typedef  TYPE_5__ svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_GET_REP ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_to_cstring_display (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_x__ensure_revision_exists (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__open_rep_cache (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_revnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__get_rep_reference(svn_fs_x__representation_t **rep_p,
                            svn_fs_t *fs,
                            svn_checksum_t *checksum,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  svn_fs_x__representation_t *rep;

  SVN_ERR_ASSERT(ffd->rep_sharing_allowed);
  if (! ffd->rep_cache_db)
    SVN_ERR(svn_fs_x__open_rep_cache(fs, scratch_pool));

  /* We only allow SHA1 checksums in this table. */
  if (checksum->kind != svn_checksum_sha1)
    return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL,
                            _("Only SHA1 checksums can be used as keys in the "
                              "rep_cache table.\n"));

  SVN_ERR(svn_sqlite__get_statement(&stmt, ffd->rep_cache_db, STMT_GET_REP));
  SVN_ERR(svn_sqlite__bindf(stmt, "s",
                            svn_checksum_to_cstring(checksum, scratch_pool)));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    {
      rep = apr_pcalloc(result_pool, sizeof(*rep));
      memcpy(rep->sha1_digest, checksum->digest, sizeof(rep->sha1_digest));
      rep->has_sha1 = TRUE;
      rep->id.change_set = svn_sqlite__column_revnum(stmt, 0);
      rep->id.number = svn_sqlite__column_int64(stmt, 1);
      rep->size = svn_sqlite__column_int64(stmt, 2);
      rep->expanded_size = svn_sqlite__column_int64(stmt, 3);
    }
  else
    rep = NULL;

  SVN_ERR(svn_sqlite__reset(stmt));

  if (rep)
    {
      /* Check that REP refers to a revision that exists in FS. */
      svn_revnum_t revision = svn_fs_x__get_revnum(rep->id.change_set);
      svn_error_t *err = svn_fs_x__ensure_revision_exists(revision, fs,
                                                          scratch_pool);
      if (err)
        return svn_error_createf(SVN_ERR_FS_CORRUPT, err,
                   "Checksum '%s' in rep-cache is beyond HEAD",
                   svn_checksum_to_cstring_display(checksum, scratch_pool));
    }

  *rep_p = rep;
  return SVN_NO_ERROR;
}