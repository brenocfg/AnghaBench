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
struct TYPE_3__ {void* data; scalar_t__ len; int /*<<< orphan*/  pool; int /*<<< orphan*/  blocksize; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  membuf_ensure (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 

void
svn_stringbuf_ensure(svn_stringbuf_t *str, apr_size_t minimum_size)
{
  void *mem = NULL;
  ++minimum_size;  /* + space for '\0' */

  membuf_ensure(&mem, &str->blocksize, minimum_size, str->pool);
  if (mem && mem != str->data)
    {
      if (str->data)
        memcpy(mem, str->data, str->len + 1);
      str->data = mem;
    }
}