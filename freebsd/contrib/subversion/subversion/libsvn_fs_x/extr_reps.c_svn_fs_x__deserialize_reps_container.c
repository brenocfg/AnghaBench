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
struct TYPE_3__ {int /*<<< orphan*/  instructions; int /*<<< orphan*/  first_instructions; int /*<<< orphan*/  bases; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ svn_fs_x__reps_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_temp_deserializer__resolve (TYPE_1__*,void**) ; 

svn_error_t *
svn_fs_x__deserialize_reps_container(void **out,
                                     void *data,
                                     apr_size_t data_len,
                                     apr_pool_t *result_pool)
{
  svn_fs_x__reps_t *reps = (svn_fs_x__reps_t *)data;

  /* de-serialize sub-structures */
  svn_temp_deserializer__resolve(reps, (void **)&reps->text);
  svn_temp_deserializer__resolve(reps, (void **)&reps->bases);
  svn_temp_deserializer__resolve(reps, (void **)&reps->first_instructions);
  svn_temp_deserializer__resolve(reps, (void **)&reps->instructions);

  /* done */
  *out = reps;

  return SVN_NO_ERROR;
}