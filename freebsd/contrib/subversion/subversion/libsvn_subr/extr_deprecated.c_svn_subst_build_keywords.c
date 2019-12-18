#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const* id; int /*<<< orphan*/  const* url; int /*<<< orphan*/  const* author; int /*<<< orphan*/  const* date; int /*<<< orphan*/  const* revision; } ;
typedef  TYPE_1__ svn_subst_keywords_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_KEYWORD_AUTHOR_LONG ; 
 int /*<<< orphan*/  SVN_KEYWORD_DATE_LONG ; 
 int /*<<< orphan*/  SVN_KEYWORD_ID ; 
 int /*<<< orphan*/  SVN_KEYWORD_REVISION_LONG ; 
 int /*<<< orphan*/  SVN_KEYWORD_URL_LONG ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_subst_build_keywords2 (int /*<<< orphan*/ **,char const*,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_subst_build_keywords(svn_subst_keywords_t *kw,
                         const char *keywords_val,
                         const char *rev,
                         const char *url,
                         apr_time_t date,
                         const char *author,
                         apr_pool_t *pool)
{
  apr_hash_t *kwhash;
  const svn_string_t *val;

  SVN_ERR(svn_subst_build_keywords2(&kwhash, keywords_val, rev,
                                    url, date, author, pool));

  /* The behaviour of pre-1.3 svn_subst_build_keywords, which we are
   * replicating here, is to write to a slot in the svn_subst_keywords_t
   * only if the relevant keyword was present in keywords_val, otherwise
   * leaving that slot untouched. */

  val = svn_hash_gets(kwhash, SVN_KEYWORD_REVISION_LONG);
  if (val)
    kw->revision = val;

  val = svn_hash_gets(kwhash, SVN_KEYWORD_DATE_LONG);
  if (val)
    kw->date = val;

  val = svn_hash_gets(kwhash, SVN_KEYWORD_AUTHOR_LONG);
  if (val)
    kw->author = val;

  val = svn_hash_gets(kwhash, SVN_KEYWORD_URL_LONG);
  if (val)
    kw->url = val;

  val = svn_hash_gets(kwhash, SVN_KEYWORD_ID);
  if (val)
    kw->id = val;

  return SVN_NO_ERROR;
}