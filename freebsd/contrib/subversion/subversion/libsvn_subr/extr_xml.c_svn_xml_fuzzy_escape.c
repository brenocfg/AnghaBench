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
struct TYPE_5__ {char const* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  escaped_char ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_snprintf (char*,int,char*,unsigned char) ; 
 int strlen (char const*) ; 
 scalar_t__ svn_ctype_iscntrl (char const) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

const char *
svn_xml_fuzzy_escape(const char *string, apr_pool_t *pool)
{
  const char *end = string + strlen(string);
  const char *p = string, *q;
  svn_stringbuf_t *outstr;
  char escaped_char[6];   /* ? \ u u u \0 */

  for (q = p; q < end; q++)
    {
      if (svn_ctype_iscntrl(*q)
          && ! ((*q == '\n') || (*q == '\r') || (*q == '\t')))
        break;
    }

  /* Return original string if no unsafe characters found. */
  if (q == end)
    return string;

  outstr = svn_stringbuf_create_empty(pool);
  while (1)
    {
      q = p;

      /* Traverse till either unsafe character or eos. */
      while ((q < end)
             && ((! svn_ctype_iscntrl(*q))
                 || (*q == '\n') || (*q == '\r') || (*q == '\t')))
        q++;

      /* copy chunk before marker */
      svn_stringbuf_appendbytes(outstr, p, q - p);

      if (q == end)
        break;

      /* Append an escaped version of the unsafe character.

         ### This format was chosen for consistency with
         ### svn_utf__cstring_from_utf8_fuzzy().  The two functions
         ### should probably share code, even though they escape
         ### different characters.
      */
      apr_snprintf(escaped_char, sizeof(escaped_char), "?\\%03u",
                   (unsigned char) *q);
      svn_stringbuf_appendcstr(outstr, escaped_char);

      p = q + 1;
    }

  return outstr->data;
}