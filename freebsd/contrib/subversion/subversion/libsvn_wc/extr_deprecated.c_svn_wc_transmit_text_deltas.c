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
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_wc_transmit_text_deltas2 (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_transmit_text_deltas(const char *path,
                            svn_wc_adm_access_t *adm_access,
                            svn_boolean_t fulltext,
                            const svn_delta_editor_t *editor,
                            void *file_baton,
                            const char **tempfile,
                            apr_pool_t *pool)
{
  return svn_wc_transmit_text_deltas2(tempfile, NULL, path, adm_access,
                                      fulltext, editor, file_baton, pool);
}