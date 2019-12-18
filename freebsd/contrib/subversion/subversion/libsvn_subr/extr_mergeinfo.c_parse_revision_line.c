#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* apr_hash_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_pathname (char const**,char const*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_rangelist (char const**,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_rangelist__canonicalize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_dup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_rangelist_merge2 (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_revision_line(const char **input, const char *end, svn_mergeinfo_t hash,
                    apr_pool_t *scratch_pool)
{
  const char *pathname = "";
  apr_ssize_t klen;
  svn_rangelist_t *existing_rangelist;
  svn_rangelist_t *rangelist = apr_array_make(scratch_pool, 1,
                                              sizeof(svn_merge_range_t *));

  SVN_ERR(parse_pathname(input, end, &pathname, scratch_pool));

  if (*(*input) != ':')
    return svn_error_create(SVN_ERR_MERGEINFO_PARSE_ERROR, NULL,
                            _("Pathname not terminated by ':'"));

  *input = *input + 1;

  SVN_ERR(parse_rangelist(input, end, rangelist, scratch_pool));

  if (rangelist->nelts == 0)
      return svn_error_createf(SVN_ERR_MERGEINFO_PARSE_ERROR, NULL,
                               _("Mergeinfo for '%s' maps to an "
                                 "empty revision range"), pathname);
  if (*input != end && *(*input) != '\n')
    return svn_error_createf(SVN_ERR_MERGEINFO_PARSE_ERROR, NULL,
                             _("Could not find end of line in range list line "
                               "in '%s'"), *input);

  if (*input != end)
    *input = *input + 1;

  /* Sort the rangelist, combine adjacent ranges into single ranges, and
     make sure there are no overlapping ranges.  Luckily, most data in
     svn:mergeinfo will already be in normalized form and this will be quick.
   */
  SVN_ERR(svn_rangelist__canonicalize(rangelist, scratch_pool));

  /* Handle any funky mergeinfo with relative merge source paths that
     might exist due to issue #3547.  It's possible that this issue allowed
     the creation of mergeinfo with path keys that differ only by a
     leading slash, e.g. "trunk:4033\n/trunk:4039-4995".  In the event
     we encounter this we merge the rangelists together under a single
     absolute path key. */
  klen = strlen(pathname);
  existing_rangelist = apr_hash_get(hash, pathname, klen);
  if (existing_rangelist)
    SVN_ERR(svn_rangelist_merge2(rangelist, existing_rangelist,
                                 scratch_pool, scratch_pool));

  apr_hash_set(hash, apr_pstrmemdup(apr_hash_pool_get(hash), pathname, klen),
               klen, svn_rangelist_dup(rangelist, apr_hash_pool_get(hash)));

  return SVN_NO_ERROR;
}