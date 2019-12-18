#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__representation_t ;
typedef  int /*<<< orphan*/  svn_fs_x__rep_header_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  shared_file_t ;
typedef  int /*<<< orphan*/  rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {char* data; } ;

/* Variables and functions */
 scalar_t__ SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* create_rep_state_body (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_createf (scalar_t__,TYPE_1__*,char*,char*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_2__* svn_fs_x__unparse_representation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_rep_state(rep_state_t **rep_state,
                 svn_fs_x__rep_header_t **rep_header,
                 shared_file_t **shared_file,
                 svn_fs_x__representation_t *rep,
                 svn_fs_t *fs,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_error_t *err = create_rep_state_body(rep_state, rep_header,
                                           shared_file, rep, fs,
                                           result_pool, scratch_pool);
  if (err && err->apr_err == SVN_ERR_FS_CORRUPT)
    {
      /* ### This always returns "-1" for transaction reps, because
         ### this particular bit of code doesn't know if the rep is
         ### stored in the protorev or in the mutable area (for props
         ### or dir contents).  It is pretty rare for FSX to *read*
         ### from the protorev file, though, so this is probably OK.
         ### And anyone going to debug corruption errors is probably
         ### going to jump straight to this comment anyway! */
      return svn_error_createf(SVN_ERR_FS_CORRUPT, err,
                               "Corrupt representation '%s'",
                               rep
                               ? svn_fs_x__unparse_representation
                                   (rep, TRUE, scratch_pool,
                                    scratch_pool)->data
                               : "(null)");
    }
  /* ### Call representation_string() ? */
  return svn_error_trace(err);
}