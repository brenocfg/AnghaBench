#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_spillbuf_t ;
typedef  int /*<<< orphan*/ * (* svn_spillbuf_read_t ) (scalar_t__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct memblock_t {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  maybe_seek (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_data (struct memblock_t**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_buffer (int /*<<< orphan*/ *,struct memblock_t*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_spillbuf__process(svn_boolean_t *exhausted,
                      svn_spillbuf_t *buf,
                      svn_spillbuf_read_t read_func,
                      void *read_baton,
                      apr_pool_t *scratch_pool)
{
  svn_boolean_t has_seeked = FALSE;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  *exhausted = FALSE;

  while (TRUE)
    {
      struct memblock_t *mem;
      svn_error_t *err;
      svn_boolean_t stop;

      svn_pool_clear(iterpool);

      /* If this call to read_data() will read from the spill file, and we
         have not seek'd the file... then do it now.  */
      if (!has_seeked)
        SVN_ERR(maybe_seek(&has_seeked, buf, iterpool));

      /* Get some content to pass to the read callback.  */
      SVN_ERR(read_data(&mem, buf, iterpool));
      if (mem == NULL)
        {
          *exhausted = TRUE;
          break;
        }

      err = read_func(&stop, read_baton, mem->data, mem->size, iterpool);

      return_buffer(buf, mem);

      if (err)
        return svn_error_trace(err);

      /* If the callbacks told us to stop, then we're done for now.  */
      if (stop)
        break;
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}