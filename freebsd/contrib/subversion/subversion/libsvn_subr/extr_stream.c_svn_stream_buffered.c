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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_BLOCK_SIZE ; 
 int /*<<< orphan*/  BUFFER_MAX_SIZE ; 
 int /*<<< orphan*/  svn_spillbuf__create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream__from_spillbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_stream_t *
svn_stream_buffered(apr_pool_t *result_pool)
{
  return svn_stream__from_spillbuf(svn_spillbuf__create(BUFFER_BLOCK_SIZE,
                                                        BUFFER_MAX_SIZE,
                                                        result_pool),
                                   result_pool);
}