#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_spillbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_EOF ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  SB_BLOCKSIZE ; 
 int /*<<< orphan*/  SB_MAXSIZE ; 
 int /*<<< orphan*/  SERF_READ_ALL_AVAIL ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ serf_bucket_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_spillbuf__create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_spillbuf__write (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__copy_into_spillbuf(svn_spillbuf_t **spillbuf,
                                serf_bucket_t *bkt,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  *spillbuf = svn_spillbuf__create(SB_BLOCKSIZE, SB_MAXSIZE, result_pool);

  /* Copy all data from the bucket into the spillbuf.  */
  while (TRUE)
    {
      apr_status_t status;
      const char *data;
      apr_size_t len;

      status = serf_bucket_read(bkt, SERF_READ_ALL_AVAIL, &data, &len);

      if (status != APR_SUCCESS && status != APR_EOF)
        return svn_ra_serf__wrap_err(status, _("Failed to read the request"));

      SVN_ERR(svn_spillbuf__write(*spillbuf, data, len, scratch_pool));

      if (status == APR_EOF)
        break;
    }

  return SVN_NO_ERROR;
}