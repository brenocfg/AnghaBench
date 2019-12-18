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
struct TYPE_3__ {int /*<<< orphan*/ * spill; int /*<<< orphan*/  spill_start; int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ svn_spillbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
maybe_seek(svn_boolean_t *seeked,
           const svn_spillbuf_t *buf,
           apr_pool_t *scratch_pool)
{
  if (buf->head == NULL && buf->spill != NULL)
    {
      apr_off_t output_unused;

      /* Seek to where we left off reading.  */
      output_unused = buf->spill_start;  /* ### stupid API  */
      SVN_ERR(svn_io_file_seek(buf->spill,
                               APR_SET, &output_unused,
                               scratch_pool));
      if (seeked != NULL)
        *seeked = TRUE;
    }
  else if (seeked != NULL)
    {
      *seeked = FALSE;
    }

  return SVN_NO_ERROR;
}