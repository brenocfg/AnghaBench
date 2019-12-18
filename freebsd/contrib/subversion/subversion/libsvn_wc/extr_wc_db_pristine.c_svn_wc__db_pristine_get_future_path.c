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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_pristine_fname (char const**,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_pristine_get_future_path(const char **pristine_abspath,
                                    const char *wcroot_abspath,
                                    const svn_checksum_t *sha1_checksum,
                                    apr_pool_t *result_pool,
                                    apr_pool_t *scratch_pool)
{
  SVN_ERR(get_pristine_fname(pristine_abspath, wcroot_abspath,
                             sha1_checksum,
                             result_pool, scratch_pool));
  return SVN_NO_ERROR;
}