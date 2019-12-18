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
struct TYPE_4__ {char const* data; int blocksize; scalar_t__ len; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 char* apr_pmemdup (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,scalar_t__) ; 

void
svn_stringbuf_insert(svn_stringbuf_t *str,
                     apr_size_t pos,
                     const char *bytes,
                     apr_size_t count)
{
  /* For COUNT==0, we allow BYTES to be NULL. It's a no-op in that case. */
  if (count == 0)
    return;

  /* special case: BYTES overlaps with this string -> copy the source */
  if (bytes + count > str->data && bytes < str->data + str->blocksize)
    bytes = apr_pmemdup(str->pool, bytes, count);

  if (pos > str->len)
    pos = str->len;

  svn_stringbuf_ensure(str, str->len + count);
  memmove(str->data + pos + count, str->data + pos, str->len - pos + 1);
  memcpy(str->data + pos, bytes, count);

  str->len += count;
}