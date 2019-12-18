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
struct sbb_baton {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/ * holding; int /*<<< orphan*/ * spillbuf; } ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  sb_bucket_vtable ; 
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sbb_baton*) ; 
 struct sbb_baton* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 

serf_bucket_t *
svn_ra_serf__create_sb_bucket(svn_spillbuf_t *spillbuf,
                              serf_bucket_alloc_t *allocator,
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  struct sbb_baton *sbb;

  sbb = serf_bucket_mem_alloc(allocator, sizeof(*sbb));
  sbb->spillbuf = spillbuf;
  sbb->holding = NULL;
  sbb->scratch_pool = svn_pool_create(result_pool);

  return serf_bucket_create(&sb_bucket_vtable, allocator, sbb);
}