#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* instructions; void* reps; void* bases; int /*<<< orphan*/  hash; int /*<<< orphan*/  text; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_x__reps_builder_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  rep_t ;
typedef  int /*<<< orphan*/  instruction_t ;
typedef  int /*<<< orphan*/  base_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_hash (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

svn_fs_x__reps_builder_t *
svn_fs_x__reps_builder_create(svn_fs_t *fs,
                              apr_pool_t *result_pool)
{
  svn_fs_x__reps_builder_t *result = apr_pcalloc(result_pool,
                                                 sizeof(*result));

  result->fs = fs;
  result->text = svn_stringbuf_create_empty(result_pool);
  init_hash(&result->hash, 4, result_pool);

  result->bases = apr_array_make(result_pool, 0, sizeof(base_t));
  result->reps = apr_array_make(result_pool, 0, sizeof(rep_t));
  result->instructions = apr_array_make(result_pool, 0,
                                        sizeof(instruction_t));

  return result;
}