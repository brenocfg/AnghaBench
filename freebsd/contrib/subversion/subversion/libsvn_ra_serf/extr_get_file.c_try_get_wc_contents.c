#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  wc_callback_baton; TYPE_1__* wc_callbacks; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* get_wc_contents ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
try_get_wc_contents(svn_boolean_t *found_p,
                    svn_ra_serf__session_t *session,
                    const char *sha1_checksum_prop,
                    svn_stream_t *dst_stream,
                    apr_pool_t *pool)
{
  svn_checksum_t *checksum;
  svn_stream_t *wc_stream;
  svn_error_t *err;

  /* No contents found by default. */
  *found_p = FALSE;

  if (!session->wc_callbacks->get_wc_contents
      || sha1_checksum_prop == NULL)
    {
      /* Nothing to do. */
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_checksum_parse_hex(&checksum, svn_checksum_sha1,
                                 sha1_checksum_prop, pool));

  err = session->wc_callbacks->get_wc_contents(
          session->wc_callback_baton, &wc_stream, checksum, pool);

  if (err)
    {
      svn_error_clear(err);

      /* Ignore errors for now. */
      return SVN_NO_ERROR;
    }

  if (wc_stream)
    {
        SVN_ERR(svn_stream_copy3(wc_stream,
                                 svn_stream_disown(dst_stream, pool),
                                 NULL, NULL, pool));
      *found_p = TRUE;
    }

  return SVN_NO_ERROR;
}