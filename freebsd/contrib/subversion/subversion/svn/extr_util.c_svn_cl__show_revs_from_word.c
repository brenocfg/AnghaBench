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
typedef  int /*<<< orphan*/  svn_cl__show_revs_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CL__SHOW_REVS_ELIGIBLE ; 
 int /*<<< orphan*/  SVN_CL__SHOW_REVS_MERGED ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cl__show_revs_eligible ; 
 int /*<<< orphan*/  svn_cl__show_revs_invalid ; 
 int /*<<< orphan*/  svn_cl__show_revs_merged ; 

svn_cl__show_revs_t
svn_cl__show_revs_from_word(const char *word)
{
  if (strcmp(word, SVN_CL__SHOW_REVS_MERGED) == 0)
    return svn_cl__show_revs_merged;
  if (strcmp(word, SVN_CL__SHOW_REVS_ELIGIBLE) == 0)
    return svn_cl__show_revs_eligible;
  /* word is an invalid flavor. */
  return svn_cl__show_revs_invalid;
}