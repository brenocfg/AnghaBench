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
struct TYPE_6__ {char const* path; } ;
struct TYPE_7__ {TYPE_1__ repos_root; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (char const**,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* svn_urlpath__skip_ancestor (char const*,char const*) ; 

svn_error_t *
svn_ra_serf__get_relative_path(const char **rel_path,
                               const char *orig_path,
                               svn_ra_serf__session_t *session,
                               apr_pool_t *pool)
{
  const char *decoded_root, *decoded_orig;

  if (! session->repos_root.path)
    {
      const char *vcc_url;

      /* This should only happen if we haven't detected HTTP v2
         support from the server.  */
      assert(! SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session));

      /* We don't actually care about the VCC_URL, but this API
         promises to populate the session's root-url cache, and that's
         what we really want. */
      SVN_ERR(svn_ra_serf__discover_vcc(&vcc_url, session,
                                        pool));
    }

  decoded_root = svn_path_uri_decode(session->repos_root.path, pool);
  decoded_orig = svn_path_uri_decode(orig_path, pool);
  *rel_path = svn_urlpath__skip_ancestor(decoded_root, decoded_orig);
  SVN_ERR_ASSERT(*rel_path != NULL);
  return SVN_NO_ERROR;
}