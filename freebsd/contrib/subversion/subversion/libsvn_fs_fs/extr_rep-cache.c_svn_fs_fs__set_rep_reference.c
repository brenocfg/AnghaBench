#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
struct TYPE_20__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_21__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_22__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ svn_checksum_t ;
struct TYPE_23__ {scalar_t__ expanded_size; scalar_t__ size; scalar_t__ item_index; scalar_t__ revision; int /*<<< orphan*/  has_sha1; int /*<<< orphan*/  sha1_digest; } ;
typedef  TYPE_4__ representation_t ;
struct TYPE_24__ {int /*<<< orphan*/  rep_cache_db; int /*<<< orphan*/  rep_sharing_allowed; } ;
typedef  TYPE_5__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SET_REP ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 scalar_t__ SVN_ERR_SQLITE_CONSTRAINT ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__get_rep_reference (TYPE_4__**,TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__open_rep_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_sqlite__insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__set_rep_reference(svn_fs_t *fs,
                             representation_t *rep,
                             apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_sqlite__stmt_t *stmt;
  svn_error_t *err;
  svn_checksum_t checksum;
  checksum.kind = svn_checksum_sha1;
  checksum.digest = rep->sha1_digest;

  SVN_ERR_ASSERT(ffd->rep_sharing_allowed);
  if (! ffd->rep_cache_db)
    SVN_ERR(svn_fs_fs__open_rep_cache(fs, pool));

  /* We only allow SHA1 checksums in this table. */
  if (! rep->has_sha1)
    return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL,
                            _("Only SHA1 checksums can be used as keys in the "
                              "rep_cache table.\n"));

  SVN_ERR(svn_sqlite__get_statement(&stmt, ffd->rep_cache_db, STMT_SET_REP));
  SVN_ERR(svn_sqlite__bindf(stmt, "siiii",
                            svn_checksum_to_cstring(&checksum, pool),
                            (apr_int64_t) rep->revision,
                            (apr_int64_t) rep->item_index,
                            (apr_int64_t) rep->size,
                            (apr_int64_t) rep->expanded_size));

  err = svn_sqlite__insert(NULL, stmt);
  if (err)
    {
      representation_t *old_rep;

      if (err->apr_err != SVN_ERR_SQLITE_CONSTRAINT)
        return svn_error_trace(err);

      svn_error_clear(err);

      /* Constraint failed so the mapping for SHA1_CHECKSUM->REP
         should exist.  If so that's cool -- just do nothing.  If not,
         that's a red flag!  */
      SVN_ERR(svn_fs_fs__get_rep_reference(&old_rep, fs, &checksum, pool));

      if (!old_rep)
        {
          /* Something really odd at this point, we failed to insert the
             checksum AND failed to read an existing checksum.  Do we need
             to flag this? */
        }
    }

  return SVN_NO_ERROR;
}