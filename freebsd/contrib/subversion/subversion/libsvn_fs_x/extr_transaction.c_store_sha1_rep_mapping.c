#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_13__ {scalar_t__ kind; TYPE_7__* data_rep; } ;
typedef  TYPE_3__ svn_fs_x__noderev_t ;
struct TYPE_14__ {scalar_t__ rep_sharing_allowed; } ;
typedef  TYPE_4__ svn_fs_x__data_t ;
struct TYPE_15__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_5__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
struct TYPE_11__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_16__ {int /*<<< orphan*/  sha1_digest; TYPE_1__ id; scalar_t__ has_sha1; } ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_TRUNCATE ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__get_txn_id (int /*<<< orphan*/ ) ; 
 char* svn_fs_x__path_txn_sha1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_fs_x__unparse_representation (TYPE_7__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 

__attribute__((used)) static svn_error_t *
store_sha1_rep_mapping(svn_fs_t *fs,
                       svn_fs_x__noderev_t *noderev,
                       apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;

  /* if rep sharing has been enabled and the noderev has a data rep and
   * its SHA-1 is known, store the rep struct under its SHA1. */
  if (   ffd->rep_sharing_allowed
      && noderev->data_rep
      && noderev->data_rep->has_sha1)
    {
      apr_file_t *rep_file;
      apr_int64_t txn_id
        = svn_fs_x__get_txn_id(noderev->data_rep->id.change_set);
      const char *file_name
        = svn_fs_x__path_txn_sha1(fs, txn_id,
                                  noderev->data_rep->sha1_digest,
                                  scratch_pool);
      svn_stringbuf_t *rep_string
        = svn_fs_x__unparse_representation(noderev->data_rep,
                                           (noderev->kind == svn_node_dir),
                                           scratch_pool, scratch_pool);

      SVN_ERR(svn_io_file_open(&rep_file, file_name,
                               APR_WRITE | APR_CREATE | APR_TRUNCATE
                               | APR_BUFFERED, APR_OS_DEFAULT, scratch_pool));

      SVN_ERR(svn_io_file_write_full(rep_file, rep_string->data,
                                     rep_string->len, NULL, scratch_pool));

      SVN_ERR(svn_io_file_close(rep_file, scratch_pool));
    }

  return SVN_NO_ERROR;
}