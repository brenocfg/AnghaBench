#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_11__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {scalar_t__ kind; } ;
typedef  TYPE_3__ svn_checksum_t ;
typedef  scalar_t__ svn_checksum_kind_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* file_checksum ) (TYPE_3__**,scalar_t__,TYPE_2__*,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,scalar_t__,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_contents (int /*<<< orphan*/ **,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_contents_checksum (TYPE_3__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_file_checksum(svn_checksum_t **checksum,
                     svn_checksum_kind_t kind,
                     svn_fs_root_t *root,
                     const char *path,
                     svn_boolean_t force,
                     apr_pool_t *pool)
{
  SVN_ERR(root->vtable->file_checksum(checksum, kind, root, path, pool));

  if (force && (*checksum == NULL || (*checksum)->kind != kind))
    {
      svn_stream_t *contents;

      SVN_ERR(svn_fs_file_contents(&contents, root, path, pool));
      SVN_ERR(svn_stream_contents_checksum(checksum, contents, kind,
                                           pool, pool));
    }

  return SVN_NO_ERROR;
}