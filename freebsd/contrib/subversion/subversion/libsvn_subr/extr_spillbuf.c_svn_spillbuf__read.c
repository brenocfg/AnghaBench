#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct memblock_t* out_for_reading; } ;
typedef  TYPE_1__ svn_spillbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct memblock_t {char* data; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  maybe_seek (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_data (struct memblock_t**,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_buffer (TYPE_1__*,struct memblock_t*) ; 

svn_error_t *
svn_spillbuf__read(const char **data,
                   apr_size_t *len,
                   svn_spillbuf_t *buf,
                   apr_pool_t *scratch_pool)
{
  struct memblock_t *mem;

  /* Possibly seek... */
  SVN_ERR(maybe_seek(NULL, buf, scratch_pool));

  SVN_ERR(read_data(&mem, buf, scratch_pool));
  if (mem == NULL)
    {
      *data = NULL;
      *len = 0;
    }
  else
    {
      *data = mem->data;
      *len = mem->size;

      /* If a block was out for reading, then return it.  */
      if (buf->out_for_reading != NULL)
        return_buffer(buf, buf->out_for_reading);

      /* Remember that we've passed this block out for reading.  */
      buf->out_for_reading = mem;
    }

  return SVN_NO_ERROR;
}