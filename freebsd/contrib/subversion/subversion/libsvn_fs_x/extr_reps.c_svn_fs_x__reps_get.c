#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* first_instructions; } ;
typedef  TYPE_1__ svn_fs_x__reps_t ;
struct TYPE_9__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  result; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ svn_fs_x__rep_extractor_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_text (TYPE_2__*,TYPE_1__ const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__reps_get(svn_fs_x__rep_extractor_t **extractor,
                   svn_fs_t *fs,
                   const svn_fs_x__reps_t *container,
                   apr_size_t idx,
                   apr_pool_t *result_pool)
{
  apr_uint32_t first = container->first_instructions[idx];
  apr_uint32_t last = container->first_instructions[idx + 1];

  /* create the extractor object */
  svn_fs_x__rep_extractor_t *result = apr_pcalloc(result_pool,
                                                  sizeof(*result));
  result->fs = fs;
  result->result = svn_stringbuf_create_empty(result_pool);
  result->pool = result_pool;

  /* fill all the bits of the result that we can, i.e. all but bits coming
   * from base representations */
  get_text(result, container, first, last - first);
  *extractor = result;
  return SVN_NO_ERROR;
}