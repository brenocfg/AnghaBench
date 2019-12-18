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
struct TYPE_4__ {scalar_t__ maxsize; scalar_t__ memory_size; scalar_t__ spill_start; scalar_t__ blocksize; struct memblock_t* tail; struct memblock_t* head; int /*<<< orphan*/  spill_size; int /*<<< orphan*/ * spill; scalar_t__ spill_all_contents; int /*<<< orphan*/  pool; scalar_t__ delete_on_close; int /*<<< orphan*/  dirpath; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ svn_spillbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct memblock_t {char const* data; scalar_t__ size; struct memblock_t* next; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct memblock_t* get_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_del_on_close ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_spillbuf__write(svn_spillbuf_t *buf,
                    const char *data,
                    apr_size_t len,
                    apr_pool_t *scratch_pool)
{
  struct memblock_t *mem;

  /* We do not (yet) have a spill file, but the amount stored in memory
     will grow too large. Create the file and place the pending data into
     the temporary file.  */
  if (buf->spill == NULL
      && ((buf->maxsize - buf->memory_size) < len))
    {
      SVN_ERR(svn_io_open_unique_file3(&buf->spill,
                                       &buf->filename,
                                       buf->dirpath,
                                       (buf->delete_on_close
                                        ? svn_io_file_del_on_close
                                        : svn_io_file_del_none),
                                       buf->pool, scratch_pool));

      /* Optionally write the memory contents into the file. */
      if (buf->spill_all_contents)
        {
          mem = buf->head;
          while (mem != NULL)
            {
              SVN_ERR(svn_io_file_write_full(buf->spill, mem->data, mem->size,
                                             NULL, scratch_pool));
              mem = mem->next;
            }

          /* Adjust the start offset for reading from the spill file.

             This way, the first `buf->memory_size` bytes of data will
             be read from the existing in-memory buffers, which makes
             more sense than discarding the buffers and re-reading
             data from the file. */
          buf->spill_start = buf->memory_size;
        }
    }

  /* Once a spill file has been constructed, then we need to put all
     arriving data into the file. We will no longer attempt to hold it
     in memory.  */
  if (buf->spill != NULL)
    {
      apr_off_t output_unused = 0;  /* ### stupid API  */

      /* Seek to the end of the spill file. We don't know if a read has
         occurred since our last write, and moved the file position.  */
      SVN_ERR(svn_io_file_seek(buf->spill,
                               APR_END, &output_unused,
                               scratch_pool));

      SVN_ERR(svn_io_file_write_full(buf->spill, data, len,
                                     NULL, scratch_pool));
      buf->spill_size += len;

      return SVN_NO_ERROR;
    }

  while (len > 0)
    {
      apr_size_t amt;

      if (buf->tail == NULL || buf->tail->size == buf->blocksize)
        {
          /* There is no existing memblock (that may have space), or the
             tail memblock has no space, so we need a new memblock.  */
          mem = get_buffer(buf);
          mem->size = 0;
          mem->next = NULL;
        }
      else
        {
          mem = buf->tail;
        }

      /* Compute how much to write into the memblock.  */
      amt = buf->blocksize - mem->size;
      if (amt > len)
        amt = len;

      /* Copy some data into this memblock.  */
      memcpy(&mem->data[mem->size], data, amt);
      mem->size += amt;
      data += amt;
      len -= amt;

      /* We need to record how much is buffered in memory. Once we reach
         buf->maxsize (or thereabouts, it doesn't have to be precise), then
         we'll switch to putting the content into a file.  */
      buf->memory_size += amt;

      /* Start a list of buffers, or (if we're not writing into the tail)
         append to the end of the linked list of buffers.  */
      if (buf->tail == NULL)
        {
          buf->head = mem;
          buf->tail = mem;
        }
      else if (mem != buf->tail)
        {
          buf->tail->next = mem;
          buf->tail = mem;
        }
    }

  return SVN_NO_ERROR;
}