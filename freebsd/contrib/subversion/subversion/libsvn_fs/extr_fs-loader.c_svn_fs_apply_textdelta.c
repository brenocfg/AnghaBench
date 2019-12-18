#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* apply_textdelta ) (int /*<<< orphan*/ *,void**,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void**,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_apply_textdelta(svn_txdelta_window_handler_t *contents_p,
                       void **contents_baton_p, svn_fs_root_t *root,
                       const char *path, const char *base_checksum,
                       const char *result_checksum, apr_pool_t *pool)
{
  svn_checksum_t *base, *result;

  /* TODO: If we ever rev this API, we should make the supplied checksums
     svn_checksum_t structs. */
  SVN_ERR(svn_checksum_parse_hex(&base, svn_checksum_md5, base_checksum,
                                 pool));
  SVN_ERR(svn_checksum_parse_hex(&result, svn_checksum_md5, result_checksum,
                                 pool));

  return svn_error_trace(root->vtable->apply_textdelta(contents_p,
                                                       contents_baton_p,
                                                       root,
                                                       path,
                                                       base,
                                                       result,
                                                       pool));
}