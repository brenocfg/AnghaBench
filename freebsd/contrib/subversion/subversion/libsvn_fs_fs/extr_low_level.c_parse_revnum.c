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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_revnum_parse (int /*<<< orphan*/ *,char const*,char const**) ; 

__attribute__((used)) static svn_error_t *
parse_revnum(svn_revnum_t *rev,
             const char **text)
{
  const char *string = *text;
  if ((string[0] == '-') && (string[1] == '1'))
    {
      *rev = SVN_INVALID_REVNUM;
      string += 2;
    }
  else
    {
      SVN_ERR(svn_revnum_parse(rev, string, &string));
    }

  if (*string == ' ')
    ++string;
  else if (*string != '\0')
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid character in revision number"));

  *text = string;
  return SVN_NO_ERROR;
}