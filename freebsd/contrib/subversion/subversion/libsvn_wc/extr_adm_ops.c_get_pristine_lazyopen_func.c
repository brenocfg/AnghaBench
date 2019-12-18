#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_checksum_t ;
struct TYPE_9__ {int /*<<< orphan*/  wri_abspath; TYPE_1__* wc_ctx; TYPE_2__* checksum; } ;
typedef  TYPE_3__ get_pristine_lazyopen_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_sha1 (TYPE_2__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_pristine_lazyopen_func(svn_stream_t **stream,
                           void *baton,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  get_pristine_lazyopen_baton_t *b = baton;
  const svn_checksum_t *sha1_checksum;

  /* svn_wc__db_pristine_read() wants a SHA1, so if we have an MD5,
     we'll use it to lookup the SHA1. */
  if (b->checksum->kind == svn_checksum_sha1)
    sha1_checksum = b->checksum;
  else
    SVN_ERR(svn_wc__db_pristine_get_sha1(&sha1_checksum, b->wc_ctx->db,
                                         b->wri_abspath, b->checksum,
                                         scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__db_pristine_read(stream, NULL, b->wc_ctx->db,
                                   b->wri_abspath, sha1_checksum,
                                   result_pool, scratch_pool));
  return SVN_NO_ERROR;
}