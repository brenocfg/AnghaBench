#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
struct TYPE_21__ {char const* data; int len; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_18__ {int const size; TYPE_5__* data; } ;
struct TYPE_22__ {TYPE_12__ rule_path_buffer; TYPE_1__* authz; TYPE_2__* rule_string_buffer; } ;
typedef  TYPE_3__ ctor_baton_t ;
struct TYPE_23__ {int len; int /*<<< orphan*/ * path; } ;
typedef  TYPE_4__ authz_rule_t ;
struct TYPE_19__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_24__ {scalar_t__ kind; TYPE_17__ pattern; } ;
typedef  TYPE_5__ authz_rule_segment_t ;
typedef  int apr_size_t ;
struct TYPE_20__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_INVALID_CONFIG ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_fnmatch_test (char const*) ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ ,int const) ; 
 scalar_t__ authz_rule_any_recursive ; 
 void* authz_rule_any_segment ; 
 scalar_t__ authz_rule_fnmatch ; 
 void* authz_rule_literal ; 
 scalar_t__ authz_rule_prefix ; 
 scalar_t__ authz_rule_suffix ; 
 int /*<<< orphan*/  intern_pattern (TYPE_3__*,TYPE_17__*,char const*,int) ; 
 int /*<<< orphan*/  interned_empty_string ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_5__*,int const) ; 
 int /*<<< orphan*/  svn_authz__reverse_string (char const*,int) ; 
 int /*<<< orphan*/  svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_membuf__resize (TYPE_12__*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_2__* const,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_2__* const,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_chop (TYPE_2__* const,int) ; 
 int /*<<< orphan*/  svn_stringbuf_leftchop (TYPE_2__* const,int) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_2__* const) ; 
 int /*<<< orphan*/  unescape_in_place (TYPE_2__* const) ; 

__attribute__((used)) static svn_error_t *
parse_rule_path(authz_rule_t *rule,
                ctor_baton_t *cb,
                svn_boolean_t glob,
                const char *path,
                apr_size_t path_len,
                const char *section)
{
  svn_stringbuf_t *const pattern = cb->rule_string_buffer;
  const char *const path_end = path + path_len;
  authz_rule_segment_t *segment;
  const char *start;
  const char *end;
  int nseg;

  SVN_ERR_ASSERT(*path == '/');

  nseg = 0;
  for (start = path; start != path_end; start = end)
    {
      apr_size_t pattern_len;

      /* Skip the leading slash and find the end of the segment. */
      end = memchr(++start, '/', path_len - 1);
      if (!end)
        end = path_end;

      pattern_len = end - start;
      path_len -= pattern_len + 1;

      if (pattern_len == 0)
        {
          if (nseg == 0)
            {
              /* This is an empty (root) path. */
              rule->len = 0;
              rule->path = NULL;
              return SVN_NO_ERROR;
            }

          /* A path with two consecutive slashes is not canonical. */
          return svn_error_createf(
              SVN_ERR_AUTHZ_INVALID_CONFIG,
              svn_error_create(SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
                               _("Found empty name in authz rule path")),
              _("Non-canonical path '%s' in authz rule [%s]"),
              path, section);
        }

      /* A path with . or .. segments is not canonical. */
      if (*start == '.'
          && (pattern_len == 1
              || (pattern_len == 2 && start[1] == '.')))
        return svn_error_createf(
            SVN_ERR_AUTHZ_INVALID_CONFIG,
            (end == start + 1
             ? svn_error_create(SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
                                _("Found '.' in authz rule path"))
             : svn_error_create(SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
                                _("Found '..' in authz rule path"))),
            _("Non-canonical path '%s' in authz rule [%s]"),
            path, section);

      /* Make space for the current segment. */
      ++nseg;
      svn_membuf__resize(&cb->rule_path_buffer, nseg * sizeof(*segment));
      segment = cb->rule_path_buffer.data;
      segment += (nseg - 1);

      if (!glob)
        {
          /* Trivial case: this is not a glob rule, so every segment
             is a literal match. */
          segment->kind = authz_rule_literal;
          intern_pattern(cb, &segment->pattern, start, pattern_len);
          continue;
        }

      /* Copy the segment into the temporary buffer. */
      svn_stringbuf_setempty(pattern);
      svn_stringbuf_appendbytes(pattern, start, pattern_len);

      if (0 == apr_fnmatch_test(pattern->data))
        {
          /* It's a literal match after all. */
          segment->kind = authz_rule_literal;
          unescape_in_place(pattern);
          intern_pattern(cb, &segment->pattern, pattern->data, pattern->len);
          continue;
        }

      if (*pattern->data == '*')
        {
          if (pattern->len == 1
              || (pattern->len == 2 && pattern->data[1] == '*'))
            {
              /* Process * and **, applying normalization as per
                 https://wiki.apache.org/subversion/AuthzImprovements. */

              authz_rule_segment_t *const prev =
                (nseg > 1 ? segment - 1 : NULL);

              if (pattern_len == 1)
                {
                  /* This is a *. Replace **|* with *|**. */
                  if (prev && prev->kind == authz_rule_any_recursive)
                    {
                      prev->kind = authz_rule_any_segment;
                      segment->kind = authz_rule_any_recursive;
                    }
                  else
                    segment->kind = authz_rule_any_segment;
                }
              else
                {
                  /* This is a **. Replace **|** with a single **. */
                  if (prev && prev->kind == authz_rule_any_recursive)
                    {
                      /* Simply drop the redundant new segment. */
                      --nseg;
                      continue;
                    }
                  else
                    segment->kind = authz_rule_any_recursive;
                }

              segment->pattern.data = interned_empty_string;
              segment->pattern.len = 0;
              continue;
            }

          /* Maybe it's a suffix match? */
          if (0 == apr_fnmatch_test(pattern->data + 1))
            {
              svn_stringbuf_leftchop(pattern, 1);
              segment->kind = authz_rule_suffix;
              unescape_in_place(pattern);
              svn_authz__reverse_string(pattern->data, pattern->len);
              intern_pattern(cb, &segment->pattern,
                             pattern->data, pattern->len);
              continue;
            }
        }

      if (pattern->data[pattern->len - 1] == '*')
        {
          /* Might be a prefix match. Note that because of the
             previous test, we already know that the pattern is longer
             than one character. */
          if (pattern->data[pattern->len - 2] != '\\')
            {
              /* OK, the * wasn't  escaped. Chop off the wildcard. */
              svn_stringbuf_chop(pattern, 1);
              if (0 == apr_fnmatch_test(pattern->data))
                {
                  segment->kind = authz_rule_prefix;
                  unescape_in_place(pattern);
                  intern_pattern(cb, &segment->pattern,
                                 pattern->data, pattern->len);
                  continue;
                }

              /* Restore the wildcard since it was not a prefix match. */
              svn_stringbuf_appendbyte(pattern, '*');
            }
        }

      /* It's a generic fnmatch pattern. */
      segment->kind = authz_rule_fnmatch;
      intern_pattern(cb, &segment->pattern, pattern->data, pattern->len);
    }

  SVN_ERR_ASSERT(nseg > 0);

  /* Copy the temporary segments array into the result pool. */
  {
    const apr_size_t path_size = nseg * sizeof(*segment);
    SVN_ERR_ASSERT(path_size <= cb->rule_path_buffer.size);

    rule->len = nseg;
    rule->path = apr_palloc(cb->authz->pool, path_size);
    memcpy(rule->path, cb->rule_path_buffer.data, path_size);
  }

  return SVN_NO_ERROR;
}