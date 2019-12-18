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
struct TYPE_3__ {scalar_t__ len; char* data; int /*<<< orphan*/  blocksize; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */

void
svn_stringbuf_leftchop(svn_stringbuf_t *str, apr_size_t nbytes)
{
  if (str->len == 0)
    return;

  if (nbytes >= str->len)
    {
      str->len = 0;
      *str->data = '\0';
    }
  else
    {
      /* Note: This will irretrievably waste nbytes of space in the
         stringbuf's pool, but unlike the alternative of memmoving the
         data, it's a constant-time operation. */
      str->data += nbytes;
      str->len -= nbytes;
      str->blocksize -= nbytes;
    }
}