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
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_7__ {char* uuid; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_RESPONSE_HEADER_BADNESS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (TYPE_2__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (char const**,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_serf__get_uuid(svn_ra_session_t *ra_session,
                      const char **uuid,
                      apr_pool_t *pool)
{
  svn_ra_serf__session_t *session = ra_session->priv;

  if (!session->uuid)
    {
      const char *vcc_url;

      /* We should never get here if we have HTTP v2 support, because
         any server with that support should be transmitting the
         UUID in the initial OPTIONS response.  */
      SVN_ERR_ASSERT(! SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session));

      /* We're not interested in vcc_url and relative_url, but this call also
         stores the repository's uuid in the session. */
      SVN_ERR(svn_ra_serf__discover_vcc(&vcc_url, session, pool));
      if (!session->uuid)
        {
          return svn_error_create(SVN_ERR_RA_DAV_RESPONSE_HEADER_BADNESS, NULL,
                                  _("The UUID property was not found on the "
                                    "resource or any of its parents"));
        }
    }

  *uuid = session->uuid;

  return SVN_NO_ERROR;
}