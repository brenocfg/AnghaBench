#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  number; int /*<<< orphan*/  date; } ;
struct TYPE_6__ {TYPE_1__ value; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_STR_TO_REV (char*) ; 
 int /*<<< orphan*/  apr_time_now () ; 
 scalar_t__ revision_from_word (TYPE_2__*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ svn_ctype_isalpha (char) ; 
 scalar_t__ svn_ctype_isdigit (char) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_opt_revision_date ; 
 int /*<<< orphan*/  svn_opt_revision_number ; 
 int /*<<< orphan*/ * svn_parse_date (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *parse_one_rev(svn_opt_revision_t *revision, char *str,
                           apr_pool_t *pool)
{
  char *end, save;

  /* Allow any number of 'r's to prefix a revision number, because
     that way if a script pastes svn output into another svn command
     (like "svn log -r${REV_COPIED_FROM_OUTPUT}"), it'll Just Work,
     even when compounded.

     As it happens, none of our special revision words begins with
     "r".  If any ever do, then this code will have to get smarter.

     Incidentally, this allows "r{DATE}".  We could avoid that with
     some trivial code rearrangement, but it's not clear what would
     be gained by doing so. */
  while (*str == 'r')
    str++;

  if (*str == '{')
    {
      svn_boolean_t matched;
      apr_time_t tm;
      svn_error_t *err;

      /* Brackets denote a date. */
      str++;
      end = strchr(str, '}');
      if (!end)
        return NULL;
      *end = '\0';
      err = svn_parse_date(&matched, &tm, str, apr_time_now(), pool);
      if (err)
        {
          svn_error_clear(err);
          return NULL;
        }
      if (!matched)
        return NULL;
      revision->kind = svn_opt_revision_date;
      revision->value.date = tm;
      return end + 1;
    }
  else if (svn_ctype_isdigit(*str))
    {
      /* It's a number. */
      end = str + 1;
      while (svn_ctype_isdigit(*end))
        end++;
      save = *end;
      *end = '\0';
      revision->kind = svn_opt_revision_number;
      revision->value.number = SVN_STR_TO_REV(str);
      *end = save;
      return end;
    }
  else if (svn_ctype_isalpha(*str))
    {
      end = str + 1;
      while (svn_ctype_isalpha(*end))
        end++;
      save = *end;
      *end = '\0';
      if (revision_from_word(revision, str) != 0)
        return NULL;
      *end = save;
      return end;
    }
  else
    return NULL;
}