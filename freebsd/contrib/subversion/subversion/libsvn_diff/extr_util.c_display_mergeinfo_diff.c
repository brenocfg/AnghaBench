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
struct TYPE_3__ {char const* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOL_STR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 char const* apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_diff2 (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_to_string (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_printf_from_utf8 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
display_mergeinfo_diff(const char *old_mergeinfo_val,
                       const char *new_mergeinfo_val,
                       const char *encoding,
                       svn_stream_t *outstream,
                       apr_pool_t *pool)
{
  apr_hash_t *old_mergeinfo_hash, *new_mergeinfo_hash, *added, *deleted;
  apr_pool_t *iterpool = svn_pool_create(pool);
  apr_hash_index_t *hi;

  if (old_mergeinfo_val)
    SVN_ERR(svn_mergeinfo_parse(&old_mergeinfo_hash, old_mergeinfo_val, pool));
  else
    old_mergeinfo_hash = NULL;

  if (new_mergeinfo_val)
    SVN_ERR(svn_mergeinfo_parse(&new_mergeinfo_hash, new_mergeinfo_val, pool));
  else
    new_mergeinfo_hash = NULL;

  SVN_ERR(svn_mergeinfo_diff2(&deleted, &added, old_mergeinfo_hash,
                              new_mergeinfo_hash,
                              TRUE, pool, pool));

  /* Print a hint for 'svn patch' or smilar tools, indicating the
   * number of reverse-merges and forward-merges. */
  SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, pool,
                                      "## -0,%u +0,%u ##%s",
                                      apr_hash_count(deleted),
                                      apr_hash_count(added),
                                      APR_EOL_STR));

  for (hi = apr_hash_first(pool, deleted);
       hi; hi = apr_hash_next(hi))
    {
      const char *from_path = apr_hash_this_key(hi);
      svn_rangelist_t *merge_revarray = apr_hash_this_val(hi);
      svn_string_t *merge_revstr;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_rangelist_to_string(&merge_revstr, merge_revarray,
                                      iterpool));

      SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, iterpool,
                                          _("   Reverse-merged %s:r%s%s"),
                                          from_path, merge_revstr->data,
                                          APR_EOL_STR));
    }

  for (hi = apr_hash_first(pool, added);
       hi; hi = apr_hash_next(hi))
    {
      const char *from_path = apr_hash_this_key(hi);
      svn_rangelist_t *merge_revarray = apr_hash_this_val(hi);
      svn_string_t *merge_revstr;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_rangelist_to_string(&merge_revstr, merge_revarray,
                                      iterpool));

      SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, iterpool,
                                          _("   Merged %s:r%s%s"),
                                          from_path, merge_revstr->data,
                                          APR_EOL_STR));
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}