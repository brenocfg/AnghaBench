#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_8__ {int /*<<< orphan*/  blncache; int /*<<< orphan*/  rev_root_stub; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (TYPE_1__*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retrieve_baseline_info (int /*<<< orphan*/ *,char const**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__blncache_get_bc_url (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__blncache_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (char const**,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__v2_get_youngest_revnum (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v1_get_youngest_revnum (int /*<<< orphan*/ *,char const**,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_baseline_info(const char **bc_url,
                  svn_revnum_t *revnum_used,
                  svn_ra_serf__session_t *session,
                  svn_revnum_t revision,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  /* If we detected HTTP v2 support on the server, we can construct
     the baseline collection URL ourselves, and fetch the latest
     revision (if needed) with an OPTIONS request.  */
  if (SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session))
    {
      if (SVN_IS_VALID_REVNUM(revision))
        {
          *revnum_used = revision;
        }
      else
        {
          SVN_ERR(svn_ra_serf__v2_get_youngest_revnum(
                    revnum_used, session, scratch_pool));
        }

      *bc_url = apr_psprintf(result_pool, "%s/%ld",
                             session->rev_root_stub, *revnum_used);
    }

  /* Otherwise, we fall back to the old VCC_URL PROPFIND hunt.  */
  else
    {
      const char *vcc_url;

      SVN_ERR(svn_ra_serf__discover_vcc(&vcc_url, session, scratch_pool));

      if (SVN_IS_VALID_REVNUM(revision))
        {
          /* First check baseline information cache. */
          SVN_ERR(svn_ra_serf__blncache_get_bc_url(bc_url,
                                                   session->blncache,
                                                   revision, result_pool));
          if (!*bc_url)
            {
              SVN_ERR(retrieve_baseline_info(NULL, bc_url, session,
                                             vcc_url, revision,
                                             result_pool, scratch_pool));
              SVN_ERR(svn_ra_serf__blncache_set(session->blncache, NULL,
                                                revision, *bc_url,
                                                scratch_pool));
            }

          *revnum_used = revision;
        }
      else
        {
          SVN_ERR(v1_get_youngest_revnum(revnum_used, bc_url,
                                         session, vcc_url,
                                         result_pool, scratch_pool));
        }
    }

  return SVN_NO_ERROR;
}