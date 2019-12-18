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
struct TYPE_4__ {int len; int blocksize; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char*,int) ; 

void
svn_stringbuf_appendbyte(svn_stringbuf_t *str, char byte)
{
  char *dest;
  apr_size_t old_len = str->len;

  /* In most cases, there will be pre-allocated memory left
   * to just write the new byte at the end of the used section
   * and terminate the string properly.
   */
  if (str->blocksize > old_len + 1)
    {
      /* The following read does not depend this write, so we
       * can issue the write first to minimize register pressure:
       * The value of old_len+1 is no longer needed; on most processors,
       * dest[old_len+1] will be calculated implicitly as part of
       * the addressing scheme.
       */
      str->len = old_len+1;

      /* Since the compiler cannot be sure that *src->data and *src
       * don't overlap, we read src->data *once* before writing
       * to *src->data. Replacing dest with str->data would force
       * the compiler to read it again after the first byte.
       */
      dest = str->data;

      /* If not already available in a register as per ABI, load
       * "byte" into the register (e.g. the one freed from old_len+1),
       * then write it to the string buffer and terminate it properly.
       *
       * Including the "byte" fetch, all operations so far could be
       * issued at once and be scheduled at the CPU's descression.
       * Most likely, no-one will soon depend on the data that will be
       * written in this function. So, no stalls there, either.
       */
      dest[old_len] = byte;
      dest[old_len+1] = '\0';
    }
  else
    {
      /* we need to re-allocate the string buffer
       * -> let the more generic implementation take care of that part
       */

      /* Depending on the ABI, "byte" is a register value. If we were
       * to take its address directly, the compiler might decide to
       * put in on the stack *unconditionally*, even if that would
       * only be necessary for this block.
       */
      char b = byte;
      svn_stringbuf_appendbytes(str, &b, 1);
    }
}