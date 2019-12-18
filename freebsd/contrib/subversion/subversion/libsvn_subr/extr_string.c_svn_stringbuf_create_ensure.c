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
struct TYPE_3__ {char* data; int /*<<< orphan*/ * pool; scalar_t__ blocksize; scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  membuf_create (void**,scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 

svn_stringbuf_t *
svn_stringbuf_create_ensure(apr_size_t blocksize, apr_pool_t *pool)
{
  void *mem;
  svn_stringbuf_t *new_string;

  ++blocksize; /* + space for '\0' */

  /* Allocate memory for svn_string_t and data in one chunk. */
  membuf_create(&mem, &blocksize, blocksize + sizeof(*new_string), pool);

  /* Initialize header and string */
  new_string = mem;
  new_string->data = (char*)mem + sizeof(*new_string);
  new_string->data[0] = '\0';
  new_string->len = 0;
  new_string->blocksize = blocksize - sizeof(*new_string);
  new_string->pool = pool;

  return new_string;
}