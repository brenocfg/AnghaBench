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
struct TYPE_5__ {int len; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 size_t LINE_DISPLAY_WIDTH ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_chop (TYPE_1__*,int) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 char* svn_utf__last_valid (char*,size_t) ; 
 size_t svn_utf_cstring_utf8_width (char*) ; 
 char const* svn_xml_fuzzy_escape (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
prepare_line_for_display(const char *line, apr_pool_t *pool)
{
  svn_stringbuf_t *buf = svn_stringbuf_create(line, pool);
  size_t width;
  size_t line_width = LINE_DISPLAY_WIDTH;
  apr_pool_t *iterpool;

  /* Trim EOL. */
  if (buf->len >= 2 &&
      buf->data[buf->len - 2] == '\r' &&
      buf->data[buf->len - 1] == '\n')
    svn_stringbuf_chop(buf, 2);
  else if (buf->len >= 1 &&
           (buf->data[buf->len - 1] == '\n' ||
            buf->data[buf->len - 1] == '\r'))
    svn_stringbuf_chop(buf, 1);

  /* Determine the on-screen width of the line. */
  width = svn_utf_cstring_utf8_width(buf->data);
  if (width == -1)
    {
      /* Determining the width failed. Try to get rid of unprintable
       * characters in the line buffer. */
      buf = svn_stringbuf_create(svn_xml_fuzzy_escape(buf->data, pool), pool);
      width = svn_utf_cstring_utf8_width(buf->data);
      if (width == -1)
        width = buf->len; /* fallback: buffer length */
    }

  /* Trim further in case line is still too long, or add padding in case
   * it is too short. */
  iterpool = svn_pool_create(pool);
  while (width > line_width)
    {
      const char *last_valid;

      svn_pool_clear(iterpool);

      svn_stringbuf_chop(buf, 1);

      /* Be careful not to invalidate the UTF-8 string by trimming
       * just part of a character. */
      last_valid = svn_utf__last_valid(buf->data, buf->len);
      if (last_valid < buf->data + buf->len)
        svn_stringbuf_chop(buf, (buf->data + buf->len) - last_valid);

      width = svn_utf_cstring_utf8_width(buf->data);
      if (width == -1)
        width = buf->len; /* fallback: buffer length */
    }
  svn_pool_destroy(iterpool);

  while (width == 0 || width < line_width)
    {
      svn_stringbuf_appendbyte(buf, ' ');
      width++;
    }

  SVN_ERR_ASSERT_NO_RETURN(width == line_width);
  return buf->data;
}