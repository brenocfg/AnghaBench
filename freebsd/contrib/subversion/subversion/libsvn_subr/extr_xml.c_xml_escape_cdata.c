#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xml_escape_cdata(svn_stringbuf_t **outstr,
                 const char *data,
                 apr_size_t len,
                 apr_pool_t *pool)
{
  const char *end = data + len;
  const char *p = data, *q;

  if (*outstr == NULL)
    *outstr = svn_stringbuf_create_empty(pool);

  while (1)
    {
      /* Find a character which needs to be quoted and append bytes up
         to that point.  Strictly speaking, '>' only needs to be
         quoted if it follows "]]", but it's easier to quote it all
         the time.

         So, why are we escaping '\r' here?  Well, according to the
         XML spec, '\r\n' gets converted to '\n' during XML parsing.
         Also, any '\r' not followed by '\n' is converted to '\n'.  By
         golly, if we say we want to escape a '\r', we want to make
         sure it remains a '\r'!  */
      q = p;
      while (q < end && *q != '&' && *q != '<' && *q != '>' && *q != '\r')
        q++;
      svn_stringbuf_appendbytes(*outstr, p, q - p);

      /* We may already be a winner.  */
      if (q == end)
        break;

      /* Append the entity reference for the character.  */
      if (*q == '&')
        svn_stringbuf_appendcstr(*outstr, "&amp;");
      else if (*q == '<')
        svn_stringbuf_appendcstr(*outstr, "&lt;");
      else if (*q == '>')
        svn_stringbuf_appendcstr(*outstr, "&gt;");
      else if (*q == '\r')
        svn_stringbuf_appendcstr(*outstr, "&#13;");

      p = q + 1;
    }
}