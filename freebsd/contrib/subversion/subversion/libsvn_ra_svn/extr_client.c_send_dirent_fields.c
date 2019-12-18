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
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int SVN_DIRENT_CREATED_REV ; 
 int SVN_DIRENT_HAS_PROPS ; 
 int SVN_DIRENT_KIND ; 
 int SVN_DIRENT_LAST_AUTHOR ; 
 int SVN_DIRENT_SIZE ; 
 int SVN_DIRENT_TIME ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SVN_DIRENT_CREATED_REV ; 
 int /*<<< orphan*/  SVN_RA_SVN_DIRENT_HAS_PROPS ; 
 int /*<<< orphan*/  SVN_RA_SVN_DIRENT_KIND ; 
 int /*<<< orphan*/  SVN_RA_SVN_DIRENT_LAST_AUTHOR ; 
 int /*<<< orphan*/  SVN_RA_SVN_DIRENT_SIZE ; 
 int /*<<< orphan*/  SVN_RA_SVN_DIRENT_TIME ; 
 int /*<<< orphan*/  svn_ra_svn__write_word (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
send_dirent_fields(svn_ra_svn_conn_t *conn,
                   apr_uint32_t dirent_fields,
                   apr_pool_t *scratch_pool)
{
  if (dirent_fields & SVN_DIRENT_KIND)
    SVN_ERR(svn_ra_svn__write_word(conn, scratch_pool,
                                   SVN_RA_SVN_DIRENT_KIND));
  if (dirent_fields & SVN_DIRENT_SIZE)
    SVN_ERR(svn_ra_svn__write_word(conn, scratch_pool,
                                   SVN_RA_SVN_DIRENT_SIZE));
  if (dirent_fields & SVN_DIRENT_HAS_PROPS)
    SVN_ERR(svn_ra_svn__write_word(conn, scratch_pool,
                                   SVN_RA_SVN_DIRENT_HAS_PROPS));
  if (dirent_fields & SVN_DIRENT_CREATED_REV)
    SVN_ERR(svn_ra_svn__write_word(conn, scratch_pool,
                                   SVN_RA_SVN_DIRENT_CREATED_REV));
  if (dirent_fields & SVN_DIRENT_TIME)
    SVN_ERR(svn_ra_svn__write_word(conn, scratch_pool,
                                   SVN_RA_SVN_DIRENT_TIME));
  if (dirent_fields & SVN_DIRENT_LAST_AUTHOR)
    SVN_ERR(svn_ra_svn__write_word(conn, scratch_pool,
                                   SVN_RA_SVN_DIRENT_LAST_AUTHOR));

  return SVN_NO_ERROR;
}