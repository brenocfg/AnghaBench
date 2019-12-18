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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_diff_file_diff4_2 (int /*<<< orphan*/ **,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_file_options_create (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_file_diff4(svn_diff_t **diff,
                    const char *original,
                    const char *modified,
                    const char *latest,
                    const char *ancestor,
                    apr_pool_t *pool)
{
  return svn_diff_file_diff4_2(diff, original, modified, latest, ancestor,
                               svn_diff_file_options_create(pool), pool);
}