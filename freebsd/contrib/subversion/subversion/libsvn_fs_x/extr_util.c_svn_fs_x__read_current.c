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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__path_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_content (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_revnum_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 

svn_error_t *
svn_fs_x__read_current(svn_revnum_t *rev,
                       svn_fs_t *fs,
                       apr_pool_t *scratch_pool)
{
  const char *str;
  svn_stringbuf_t *content;
  SVN_ERR(svn_fs_x__read_content(&content,
                                 svn_fs_x__path_current(fs, scratch_pool),
                                 scratch_pool));
  SVN_ERR(svn_revnum_parse(rev, content->data, &str));
  if (*str != '\n')
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Corrupt 'current' file"));

  return SVN_NO_ERROR;
}