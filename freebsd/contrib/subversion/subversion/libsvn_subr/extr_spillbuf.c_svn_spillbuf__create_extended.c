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
typedef  int /*<<< orphan*/  svn_spillbuf_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_spillbuf_extended (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_spillbuf_t *
svn_spillbuf__create_extended(apr_size_t blocksize,
                              apr_size_t maxsize,
                              svn_boolean_t delete_on_close,
                              svn_boolean_t spill_all_contents,
                              const char *dirpath,
                              apr_pool_t *result_pool)
{
  svn_spillbuf_t *buf = apr_pcalloc(result_pool, sizeof(*buf));
  init_spillbuf_extended(buf, blocksize, maxsize,
                         delete_on_close, spill_all_contents, dirpath,
                         result_pool);
  return buf;
}