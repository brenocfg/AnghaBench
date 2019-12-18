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
struct TYPE_5__ {char const* data; int blocksize; scalar_t__ len; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 char* apr_pmemdup (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_remove (TYPE_1__*,scalar_t__,scalar_t__) ; 

void
svn_stringbuf_replace(svn_stringbuf_t *str,
                      apr_size_t pos,
                      apr_size_t old_count,
                      const char *bytes,
                      apr_size_t new_count)
{
  /* For COUNT==0, we allow BYTES to be NULL.
   * In that case, this is just a substring removal. */
  if (new_count == 0)
    {
      svn_stringbuf_remove(str, pos, old_count);
      return;
    }

  /* special case: BYTES overlaps with this string -> copy the source */
  if (bytes + new_count > str->data && bytes < str->data + str->blocksize)
    bytes = apr_pmemdup(str->pool, bytes, new_count);

  if (pos > str->len)
    pos = str->len;
  if (old_count > str->len - pos)
    old_count = str->len - pos;

  if (old_count < new_count)
    {
      apr_size_t delta = new_count - old_count;
      svn_stringbuf_ensure(str, str->len + delta);
    }

  if (old_count != new_count)
    memmove(str->data + pos + new_count, str->data + pos + old_count,
            str->len - pos - old_count + 1);

  memcpy(str->data + pos, bytes, new_count);
  str->len += new_count - old_count;
}