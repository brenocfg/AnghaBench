#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int BASE64_LINELEN ; 
 int BYTES_PER_LINE ; 
 int /*<<< orphan*/  encode_group (unsigned char*,char*) ; 
 int /*<<< orphan*/  encode_line (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
encode_bytes(svn_stringbuf_t *str, const void *data, apr_size_t len,
             unsigned char *inbuf, size_t *inbuflen, size_t *linelen,
             svn_boolean_t break_lines)
{
  char group[4];
  const char *p = data, *end = p + len;
  apr_size_t buflen;

  /* Resize the stringbuf to make room for the (approximate) size of
     output, to avoid repeated resizes later.
     Please note that our optimized code relies on the fact that STR
     never needs to be resized until we leave this function. */
  buflen = len * 4 / 3 + 4;
  if (break_lines)
    {
      /* Add an extra space for line breaks. */
      buflen += buflen / BASE64_LINELEN;
    }
  svn_stringbuf_ensure(str, str->len + buflen);

  /* Keep encoding three-byte groups until we run out.  */
  while ((end - p) >= (3 - *inbuflen))
    {
      /* May we encode BYTES_PER_LINE bytes without caring about
         line breaks, data in the temporary INBUF or running out
         of data? */
      if (   *inbuflen == 0
          && (*linelen == 0 || !break_lines)
          && (end - p >= BYTES_PER_LINE))
        {
          /* Yes, we can encode a whole chunk of data at once. */
          encode_line(str, p);
          p += BYTES_PER_LINE;
          *linelen += BASE64_LINELEN;
        }
      else
        {
          /* No, this is one of a number of special cases.
             Encode the data byte by byte. */
          memcpy(inbuf + *inbuflen, p, 3 - *inbuflen);
          p += (3 - *inbuflen);
          encode_group(inbuf, group);
          svn_stringbuf_appendbytes(str, group, 4);
          *inbuflen = 0;
          *linelen += 4;
        }

      /* Add line breaks as necessary. */
      if (break_lines && *linelen == BASE64_LINELEN)
        {
          svn_stringbuf_appendbyte(str, '\n');
          *linelen = 0;
        }
    }

  /* Tack any extra input onto *INBUF.  */
  memcpy(inbuf + *inbuflen, p, end - p);
  *inbuflen += (end - p);
}