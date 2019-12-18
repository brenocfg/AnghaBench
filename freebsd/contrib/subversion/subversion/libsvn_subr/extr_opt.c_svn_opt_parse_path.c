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
struct TYPE_6__ {scalar_t__ number; } ;
struct TYPE_7__ {scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char const* strrchr (char const*,char) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  svn_opt__split_arg_at_peg_revision (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int svn_opt_parse_revision (TYPE_2__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 char* svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_opt_parse_path(svn_opt_revision_t *rev,
                   const char **truepath,
                   const char *path /* UTF-8! */,
                   apr_pool_t *pool)
{
  const char *peg_rev;

  SVN_ERR(svn_opt__split_arg_at_peg_revision(truepath, &peg_rev, path, pool));

  /* Parse the peg revision, if one was found */
  if (strlen(peg_rev))
    {
      int ret;
      svn_opt_revision_t start_revision, end_revision;

      end_revision.kind = svn_opt_revision_unspecified;

      if (peg_rev[1] == '\0')  /* looking at empty peg revision */
        {
          ret = 0;
          start_revision.kind = svn_opt_revision_unspecified;
          start_revision.value.number = 0;
        }
      else  /* looking at non-empty peg revision */
        {
          const char *rev_str = &peg_rev[1];

          /* URLs get treated differently from wc paths. */
          if (svn_path_is_url(path))
            {
              /* URLs are URI-encoded, so we look for dates with
                 URI-encoded delimiters.  */
              size_t rev_len = strlen(rev_str);
              if (rev_len > 6
                  && rev_str[0] == '%'
                  && rev_str[1] == '7'
                  && (rev_str[2] == 'B'
                      || rev_str[2] == 'b')
                  && rev_str[rev_len-3] == '%'
                  && rev_str[rev_len-2] == '7'
                  && (rev_str[rev_len-1] == 'D'
                      || rev_str[rev_len-1] == 'd'))
                {
                  rev_str = svn_path_uri_decode(rev_str, pool);
                }
            }
          ret = svn_opt_parse_revision(&start_revision,
                                       &end_revision,
                                       rev_str, pool);
        }

      if (ret || end_revision.kind != svn_opt_revision_unspecified)
        {
          /* If an svn+ssh URL was used and it contains only one @,
           * provide an error message that presents a possible solution
           * to the parsing error (issue #2349). */
          if (strncmp(path, "svn+ssh://", 10) == 0)
            {
              const char *at;

              at = strchr(path, '@');
              if (at && strrchr(path, '@') == at)
                return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                         _("Syntax error parsing peg revision "
                                           "'%s'; did you mean '%s@'?"),
                                       &peg_rev[1], path);
            }

          return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                   _("Syntax error parsing peg revision '%s'"),
                                   &peg_rev[1]);
        }
      rev->kind = start_revision.kind;
      rev->value = start_revision.value;
    }
  else
    {
      /* Didn't find a peg revision. */
      rev->kind = svn_opt_revision_unspecified;
    }

  return SVN_NO_ERROR;
}