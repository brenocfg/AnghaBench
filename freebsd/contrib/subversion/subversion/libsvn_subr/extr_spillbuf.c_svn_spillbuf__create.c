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
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_spillbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_spillbuf_t *
svn_spillbuf__create(apr_size_t blocksize,
                     apr_size_t maxsize,
                     apr_pool_t *result_pool)
{
  svn_spillbuf_t *buf = apr_pcalloc(result_pool, sizeof(*buf));
  init_spillbuf(buf, blocksize, maxsize, result_pool);
  return buf;
}