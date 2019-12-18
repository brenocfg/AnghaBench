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
struct TYPE_3__ {int blocksize; struct memblock_t* avail; int /*<<< orphan*/  pool; struct memblock_t* out_for_reading; } ;
typedef  TYPE_1__ svn_spillbuf_t ;
struct memblock_t {struct memblock_t* next; void* data; } ;

/* Variables and functions */
 void* apr_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct memblock_t *
get_buffer(svn_spillbuf_t *buf)
{
  struct memblock_t *mem = buf->out_for_reading;

  if (mem != NULL)
    {
      buf->out_for_reading = NULL;
      return mem;
    }

  if (buf->avail == NULL)
    {
      mem = apr_palloc(buf->pool, sizeof(*mem));
      mem->data = apr_palloc(buf->pool, buf->blocksize);
      return mem;
    }

  mem = buf->avail;
  buf->avail = mem->next;
  return mem;
}