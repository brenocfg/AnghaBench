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
struct TYPE_3__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

void
svn_stringbuf_remove(svn_stringbuf_t *str,
                     apr_size_t pos,
                     apr_size_t count)
{
  if (pos > str->len)
    pos = str->len;
  if (count > str->len - pos)
    count = str->len - pos;

  memmove(str->data + pos, str->data + pos + count, str->len - pos - count + 1);
  str->len -= count;
}