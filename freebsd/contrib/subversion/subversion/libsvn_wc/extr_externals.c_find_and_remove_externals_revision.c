#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; } ;
struct TYPE_6__ {TYPE_3__ revision; } ;
typedef  TYPE_1__ svn_wc_external_item2_t ;
struct TYPE_7__ {scalar_t__ member_0; scalar_t__ kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CLIENT_INVALID_EXTERNALS_DESCRIPTION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXTERNALS ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ svn_opt_parse_revision (TYPE_3__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_opt_revision_date ; 
 scalar_t__ svn_opt_revision_number ; 
 scalar_t__ svn_opt_revision_unspecified ; 

__attribute__((used)) static svn_error_t *
find_and_remove_externals_revision(int *rev_idx,
                                   const char **rev_str,
                                   const char **line_parts,
                                   int num_line_parts,
                                   svn_wc_external_item2_t *item,
                                   const char *parent_directory_display,
                                   const char *line,
                                   apr_pool_t *pool)
{
  int i;

  for (i = 0; i < 2; ++i)
    {
      const char *token = line_parts[i];

      if (token[0] == '-' && token[1] == 'r')
        {
          svn_opt_revision_t end_revision = { svn_opt_revision_unspecified };
          const char *digits_ptr;
          int shift_count;
          int j;

          *rev_idx = i;

          if (token[2] == '\0')
            {
              /* There must be a total of four elements in the line if
                 -r N is used. */
              if (num_line_parts != 4)
                goto parse_error;

              shift_count = 2;
              digits_ptr = line_parts[i+1];
            }
          else
            {
              /* There must be a total of three elements in the line
                 if -rN is used. */
              if (num_line_parts != 3)
                goto parse_error;

              shift_count = 1;
              digits_ptr = token+2;
            }

          if (svn_opt_parse_revision(&item->revision,
                                     &end_revision,
                                     digits_ptr, pool) != 0)
            goto parse_error;
          /* We want a single revision, not a range. */
          if (end_revision.kind != svn_opt_revision_unspecified)
            goto parse_error;
          /* Allow only numbers and dates, not keywords. */
          if (item->revision.kind != svn_opt_revision_number
              && item->revision.kind != svn_opt_revision_date)
            goto parse_error;

          /* Shift any line elements past the revision specification
             down over the revision specification. */
          for (j = i; j < num_line_parts-shift_count; ++j)
            line_parts[j] = line_parts[j+shift_count];
          line_parts[num_line_parts-shift_count] = NULL;

          *rev_str = apr_psprintf(pool, "-r%s", digits_ptr);

          /* Found the revision, so leave the function immediately, do
           * not continue looking for additional revisions. */
          return SVN_NO_ERROR;
        }
    }

  /* No revision was found, so there must be exactly two items in the
     line array. */
  if (num_line_parts == 2)
    return SVN_NO_ERROR;

 parse_error:
  return svn_error_createf
    (SVN_ERR_CLIENT_INVALID_EXTERNALS_DESCRIPTION, NULL,
     _("Error parsing %s property on '%s': '%s'"),
     SVN_PROP_EXTERNALS,
     parent_directory_display,
     line);
}