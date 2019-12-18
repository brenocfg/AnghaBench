#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_6__ {TYPE_3__ noderev_id; } ;
typedef  TYPE_1__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  rep_write_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  rep_write_contents ; 
 int /*<<< orphan*/  rep_write_contents_close ; 
 int /*<<< orphan*/  rep_write_get_baton (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_fs_x__id_unparse (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
set_representation(svn_stream_t **contents_p,
                   svn_fs_t *fs,
                   svn_fs_x__noderev_t *noderev,
                   apr_pool_t *result_pool)
{
  rep_write_baton_t *wb;

  if (! svn_fs_x__is_txn(noderev->noderev_id.change_set))
    return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                             _("Attempted to write to non-transaction '%s'"),
                             svn_fs_x__id_unparse(&noderev->noderev_id,
                                                  result_pool)->data);

  SVN_ERR(rep_write_get_baton(&wb, fs, noderev, result_pool));

  *contents_p = svn_stream_create(wb, result_pool);
  svn_stream_set_write(*contents_p, rep_write_contents);
  svn_stream_set_close(*contents_p, rep_write_contents_close);

  return SVN_NO_ERROR;
}