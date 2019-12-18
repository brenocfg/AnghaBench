#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char const* APR_EOL_STR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  stream_write (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* svn_cl__local_style_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline__print_prop_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 scalar_t__ svn_prop_needs_translation (char const*) ; 
 int /*<<< orphan*/  svn_subst_detranslate_string (TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_translate_cstring2 (char const*,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
print_single_prop(svn_string_t *propval,
                  const char *target_abspath_or_url,
                  const char *abspath_or_URL,
                  const char *wc_path_prefix,
                  svn_stream_t *out,
                  const char *pname,
                  svn_boolean_t print_filenames,
                  svn_boolean_t omit_newline,
                  svn_boolean_t like_proplist,
                  svn_boolean_t inherited_property,
                  apr_pool_t *scratch_pool)
{
  if (print_filenames)
    {
      const char *header;

      /* Print the file name. */

      if (! svn_path_is_url(abspath_or_URL))
        abspath_or_URL = svn_cl__local_style_skip_ancestor(wc_path_prefix,
                                                           abspath_or_URL,
                                                           scratch_pool);

      /* In verbose mode, print exactly same as "proplist" does;
       * otherwise, print a brief header. */
      if (inherited_property)
        {
          if (like_proplist)
            {
              if (! svn_path_is_url(target_abspath_or_url))
                target_abspath_or_url =
                  svn_cl__local_style_skip_ancestor(wc_path_prefix,
                                                    target_abspath_or_url,
                                                    scratch_pool);
              header = apr_psprintf(
                scratch_pool,
                _("Inherited properties on '%s',\nfrom '%s':\n"),
                target_abspath_or_url, abspath_or_URL);
            }
          else
            {
              header = apr_psprintf(scratch_pool, "%s - ", abspath_or_URL);
            }
        }
      else
        header = apr_psprintf(scratch_pool, like_proplist
                              ? _("Properties on '%s':\n")
                              : "%s - ", abspath_or_URL);
      SVN_ERR(svn_cmdline_cstring_from_utf8(&header, header, scratch_pool));
      SVN_ERR(svn_subst_translate_cstring2(header, &header,
                                           APR_EOL_STR,  /* 'native' eol */
                                           FALSE, /* no repair */
                                           NULL,  /* no keywords */
                                           FALSE, /* no expansion */
                                           scratch_pool));
      SVN_ERR(stream_write(out, header, strlen(header)));
    }

  if (like_proplist)
    {
      /* Print the property name and value just as "proplist -v" does */
      apr_hash_t *hash = apr_hash_make(scratch_pool);

      svn_hash_sets(hash, pname, propval);
      SVN_ERR(svn_cmdline__print_prop_hash(out, hash, FALSE, scratch_pool));
    }
  else
    {
      /* If this is a special Subversion property, it is stored as
         UTF8, so convert to the native format. */
      if (svn_prop_needs_translation(pname))
        SVN_ERR(svn_subst_detranslate_string(&propval, propval,
                                             TRUE, scratch_pool));

      SVN_ERR(stream_write(out, propval->data, propval->len));

      if (! omit_newline)
        SVN_ERR(stream_write(out, APR_EOL_STR,
                             strlen(APR_EOL_STR)));
    }
  return SVN_NO_ERROR;
}