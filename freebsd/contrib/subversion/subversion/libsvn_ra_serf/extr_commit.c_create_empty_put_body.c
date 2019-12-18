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
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SERF_BUCKET_SIMPLE_STRING (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
create_empty_put_body(serf_bucket_t **body_bkt,
                      void *baton,
                      serf_bucket_alloc_t *alloc,
                      apr_pool_t *pool /* request pool */,
                      apr_pool_t *scratch_pool)
{
  *body_bkt = SERF_BUCKET_SIMPLE_STRING("", alloc);
  return SVN_NO_ERROR;
}