#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_md5 (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__node_get_md5_from_sha1(const svn_checksum_t **md5_checksum,
                               svn_wc_context_t *wc_ctx,
                               const char *wri_abspath,
                               const svn_checksum_t *sha1_checksum,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  return svn_error_trace(svn_wc__db_pristine_get_md5(md5_checksum,
                                                     wc_ctx->db,
                                                     wri_abspath,
                                                     sha1_checksum,
                                                     result_pool,
                                                     scratch_pool));
}