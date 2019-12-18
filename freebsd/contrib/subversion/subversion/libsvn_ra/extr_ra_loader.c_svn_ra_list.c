#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_7__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_dirent_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_6__ {int /*<<< orphan*/ * (* list ) (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_LIST ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra__assert_capable_server (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_ra_list(svn_ra_session_t *session,
            const char *path,
            svn_revnum_t revision,
            const apr_array_header_t *patterns,
            svn_depth_t depth,
            apr_uint32_t dirent_fields,
            svn_ra_dirent_receiver_t receiver,
            void *receiver_baton,
            apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT(svn_relpath_is_canonical(path));
  if (!session->vtable->list)
    return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL, NULL);

  SVN_ERR(svn_ra__assert_capable_server(session, SVN_RA_CAPABILITY_LIST,
                                        NULL, scratch_pool));

  return session->vtable->list(session, path, revision, patterns, depth,
                               dirent_fields, receiver, receiver_baton,
                               scratch_pool);
}