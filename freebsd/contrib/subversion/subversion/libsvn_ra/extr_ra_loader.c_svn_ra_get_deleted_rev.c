#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_14__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {TYPE_3__* (* get_deleted_rev ) (TYPE_2__*,char const*,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 scalar_t__ SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* stub1 (TYPE_2__*,char const*,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* svn_ra__get_deleted_rev_from_log (TYPE_2__*,char const*,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_ra_get_deleted_rev(svn_ra_session_t *session,
                       const char *path,
                       svn_revnum_t peg_revision,
                       svn_revnum_t end_revision,
                       svn_revnum_t *revision_deleted,
                       apr_pool_t *pool)
{
  svn_error_t *err;

  /* Path must be relative. */
  SVN_ERR_ASSERT(svn_relpath_is_canonical(path));

  if (!SVN_IS_VALID_REVNUM(peg_revision))
    return svn_error_createf(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                             _("Invalid peg revision %ld"), peg_revision);
  if (!SVN_IS_VALID_REVNUM(end_revision))
    return svn_error_createf(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                             _("Invalid end revision %ld"), end_revision);
  if (end_revision <= peg_revision)
    return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                            _("Peg revision must precede end revision"));
  err = session->vtable->get_deleted_rev(session, path,
                                         peg_revision,
                                         end_revision,
                                         revision_deleted,
                                         pool);
  if (err && (err->apr_err == SVN_ERR_UNSUPPORTED_FEATURE))
    {
      svn_error_clear(err);

      /* Do it the slow way, using get-logs, for older servers. */
      err = svn_ra__get_deleted_rev_from_log(session, path, peg_revision,
                                             end_revision, revision_deleted,
                                             pool);
    }
  return err;
}