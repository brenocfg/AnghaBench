#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_6__ {char const* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
struct TYPE_7__ {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
typedef  TYPE_2__ apr_time_exp_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_time_exp_gmt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 char const* svn_time_to_human_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_uri_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_string_t *
keyword_printf(const char *fmt,
               const char *rev,
               const char *url,
               const char *repos_root_url,
               apr_time_t date,
               const char *author,
               apr_pool_t *pool)
{
  svn_stringbuf_t *value = svn_stringbuf_create_empty(pool);
  const char *cur;
  size_t n;

  for (;;)
    {
      cur = fmt;

      while (*cur != '\0' && *cur != '%')
        cur++;

      if ((n = cur - fmt) > 0) /* Do we have an as-is string? */
        svn_stringbuf_appendbytes(value, fmt, n);

      if (*cur == '\0')
        break;

      switch (cur[1])
        {
        case 'a': /* author of this revision */
          if (author)
            svn_stringbuf_appendcstr(value, author);
          break;
        case 'b': /* basename of this file */
          if (url && *url)
            {
              const char *base_name = svn_uri_basename(url, pool);
              svn_stringbuf_appendcstr(value, base_name);
            }
          break;
        case 'd': /* short format of date of this revision */
          if (date)
            {
              apr_time_exp_t exploded_time;
              const char *human;

              apr_time_exp_gmt(&exploded_time, date);

              human = apr_psprintf(pool, "%04d-%02d-%02d %02d:%02d:%02dZ",
                                   exploded_time.tm_year + 1900,
                                   exploded_time.tm_mon + 1,
                                   exploded_time.tm_mday,
                                   exploded_time.tm_hour,
                                   exploded_time.tm_min,
                                   exploded_time.tm_sec);

              svn_stringbuf_appendcstr(value, human);
            }
          break;
        case 'D': /* long format of date of this revision */
          if (date)
            svn_stringbuf_appendcstr(value,
                                     svn_time_to_human_cstring(date, pool));
          break;
        case 'P': /* relative path of this file */
          if (repos_root_url && *repos_root_url != '\0' && url && *url != '\0')
            {
              const char *repos_relpath;

              repos_relpath = svn_uri_skip_ancestor(repos_root_url, url, pool);
              if (repos_relpath)
                svn_stringbuf_appendcstr(value, repos_relpath);
            }
          break;
        case 'R': /* root of repos */
          if (repos_root_url && *repos_root_url != '\0')
            svn_stringbuf_appendcstr(value, repos_root_url);
          break;
        case 'r': /* number of this revision */
          if (rev)
            svn_stringbuf_appendcstr(value, rev);
          break;
        case 'u': /* URL of this file */
          if (url)
            svn_stringbuf_appendcstr(value, url);
          break;
        case '_': /* '%_' => a space */
          svn_stringbuf_appendbyte(value, ' ');
          break;
        case '%': /* '%%' => a literal % */
          svn_stringbuf_appendbyte(value, *cur);
          break;
        case '\0': /* '%' as the last character of the string. */
          svn_stringbuf_appendbyte(value, *cur);
          /* Now go back one character, since this was just a one character
           * sequence, whereas all others are two characters, and we do not
           * want to skip the null terminator entirely and carry on
           * formatting random memory contents. */
          cur--;
          break;
        case 'H':
          {
            svn_string_t *s = keyword_printf("%P%_%r%_%d%_%a", rev, url,
                                             repos_root_url, date, author,
                                             pool);
            svn_stringbuf_appendcstr(value, s->data);
          }
          break;
        case 'I':
          {
            svn_string_t *s = keyword_printf("%b%_%r%_%d%_%a", rev, url,
                                             repos_root_url, date, author,
                                             pool);
            svn_stringbuf_appendcstr(value, s->data);
          }
          break;
        default: /* Unrecognized code, just print it literally. */
          svn_stringbuf_appendbytes(value, cur, 2);
          break;
        }

      /* Format code is processed - skip it, and get ready for next chunk. */
      fmt = cur + 2;
    }

  return svn_stringbuf__morph_into_string(value);
}