#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__rep_header_t ;
struct TYPE_14__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  shared_file_t ;
typedef  int /*<<< orphan*/  representation_t ;
typedef  int /*<<< orphan*/  rep_state_t ;
struct TYPE_15__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_16__ {char* data; } ;

/* Variables and functions */
 scalar_t__ SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* create_rep_state_body (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_error_createf (scalar_t__,TYPE_2__*,char*,char const*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_4__* svn_fs_fs__unparse_representation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_rep_state(rep_state_t **rep_state,
                 svn_fs_fs__rep_header_t **rep_header,
                 shared_file_t **shared_file,
                 representation_t *rep,
                 svn_fs_t *fs,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_error_t *err = create_rep_state_body(rep_state, rep_header,
                                           shared_file, rep, fs,
                                           result_pool, scratch_pool);
  if (err && err->apr_err == SVN_ERR_FS_CORRUPT)
    {
      fs_fs_data_t *ffd = fs->fsap_data;
      const char *rep_str;

      /* ### This always returns "-1" for transaction reps, because
         ### this particular bit of code doesn't know if the rep is
         ### stored in the protorev or in the mutable area (for props
         ### or dir contents).  It is pretty rare for FSFS to *read*
         ### from the protorev file, though, so this is probably OK.
         ### And anyone going to debug corruption errors is probably
         ### going to jump straight to this comment anyway! */
      rep_str = rep
              ? svn_fs_fs__unparse_representation
                  (rep, ffd->format, TRUE, scratch_pool, scratch_pool)->data
              : "(null)";

      return svn_error_createf(SVN_ERR_FS_CORRUPT, err,
                               "Corrupt representation '%s'",
                               rep_str);
    }
  /* ### Call representation_string() ? */
  return svn_error_trace(err);
}