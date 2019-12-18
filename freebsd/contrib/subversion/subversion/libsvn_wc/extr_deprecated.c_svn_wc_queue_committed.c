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
typedef  int /*<<< orphan*/  svn_wc_committed_queue_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_checksum__from_digest_md5 (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__get_committed_queue_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_queue_committed2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_queue_committed(svn_wc_committed_queue_t **queue,
                       const char *path,
                       svn_wc_adm_access_t *adm_access,
                       svn_boolean_t recurse,
                       const apr_array_header_t *wcprop_changes,
                       svn_boolean_t remove_lock,
                       svn_boolean_t remove_changelist,
                       const unsigned char *digest,
                       apr_pool_t *pool)
{
  const svn_checksum_t *md5_checksum;

  if (digest)
    md5_checksum = svn_checksum__from_digest_md5(
                     digest, svn_wc__get_committed_queue_pool(*queue));
  else
    md5_checksum = NULL;

  return svn_wc_queue_committed2(*queue, path, adm_access, recurse,
                                 wcprop_changes, remove_lock,
                                 remove_changelist, md5_checksum, pool);
}