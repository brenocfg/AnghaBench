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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct dump_filter_baton_t {scalar_t__ do_exclude; int /*<<< orphan*/  prefixes; scalar_t__ glob; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int ary_prefix_match (int /*<<< orphan*/ ,char const*) ; 
 int svn_cstring_match_glob_list (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
dump_filter_func(svn_boolean_t *include,
                 svn_fs_root_t *root,
                 const char *path,
                 void *baton,
                 apr_pool_t *scratch_pool)
{
  struct dump_filter_baton_t *b = baton;
  const svn_boolean_t matches =
    (b->glob
     ? svn_cstring_match_glob_list(path, b->prefixes)
     : ary_prefix_match(b->prefixes, path));

  *include = b->do_exclude ? !matches : matches;
  return SVN_NO_ERROR;
}