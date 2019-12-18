#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ spill_size; scalar_t__ blocksize; scalar_t__ spill_start; int /*<<< orphan*/ * spill; int /*<<< orphan*/  memory_size; struct memblock_t* head; struct memblock_t* tail; } ;
typedef  TYPE_1__ svn_spillbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct memblock_t {scalar_t__ size; int /*<<< orphan*/  data; struct memblock_t* next; } ;
typedef  scalar_t__ apr_uint64_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct memblock_t* get_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  return_buffer (TYPE_1__*,struct memblock_t*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_data(struct memblock_t **mem,
          svn_spillbuf_t *buf,
          apr_pool_t *scratch_pool)
{
  svn_error_t *err;

  /* If we have some in-memory blocks, then return one.  */
  if (buf->head != NULL)
    {
      *mem = buf->head;
      if (buf->tail == *mem)
        buf->head = buf->tail = NULL;
      else
        buf->head = (*mem)->next;

      /* We're using less memory now. If we haven't hit the spill file,
         then we may be able to keep using memory.  */
      buf->memory_size -= (*mem)->size;

      return SVN_NO_ERROR;
    }

  /* No file? Done.  */
  if (buf->spill == NULL)
    {
      *mem = NULL;
      return SVN_NO_ERROR;
    }

  /* Assume that the caller has seeked the spill file to the correct pos.  */

  /* Get a buffer that we can read content into.  */
  *mem = get_buffer(buf);
  /* NOTE: mem's size/next are uninitialized.  */

  if ((apr_uint64_t)buf->spill_size < (apr_uint64_t)buf->blocksize)
    (*mem)->size = (apr_size_t)buf->spill_size;
  else
    (*mem)->size = buf->blocksize;  /* The size of (*mem)->data  */
  (*mem)->next = NULL;

  /* Read some data from the spill file into the memblock.  */
  err = svn_io_file_read(buf->spill, (*mem)->data, &(*mem)->size,
                         scratch_pool);
  if (err)
    {
      return_buffer(buf, *mem);
      return svn_error_trace(err);
    }

  /* Mark the data that we consumed from the spill file.  */
  buf->spill_start += (*mem)->size;

  /* Did we consume all the data from the spill file?  */
  if ((buf->spill_size -= (*mem)->size) == 0)
    {
      /* Close and reset our spill file information.  */
      SVN_ERR(svn_io_file_close(buf->spill, scratch_pool));
      buf->spill = NULL;
      buf->spill_start = 0;
    }

  /* *mem has been initialized. Done.  */
  return SVN_NO_ERROR;
}