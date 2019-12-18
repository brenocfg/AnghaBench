#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_4__ {TYPE_2__* result; int /*<<< orphan*/ * missing; } ;
typedef  TYPE_1__ svn_fs_x__rep_extractor_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {scalar_t__ len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_stringbuf_dup (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_ncreate (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__extractor_drive(svn_stringbuf_t **contents,
                          svn_fs_x__rep_extractor_t *extractor,
                          apr_size_t start_offset,
                          apr_size_t size,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  /* we don't support base reps right now */
  SVN_ERR_ASSERT(extractor->missing == NULL);

  if (size == 0)
    {
      *contents = svn_stringbuf_dup(extractor->result, result_pool);
    }
  else
    {
      /* clip the selected range */
      if (start_offset > extractor->result->len)
        start_offset = extractor->result->len;

      if (size > extractor->result->len - start_offset)
        size = extractor->result->len - start_offset;

      *contents = svn_stringbuf_ncreate(extractor->result->data + start_offset,
                                        size, result_pool);
    }

  return SVN_NO_ERROR;
}