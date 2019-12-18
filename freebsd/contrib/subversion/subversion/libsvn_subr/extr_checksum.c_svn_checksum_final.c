#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
struct TYPE_7__ {int kind; int /*<<< orphan*/  apr_ctx; } ;
typedef  TYPE_2__ svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_md5_final (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_sha1_final (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_checksum_create (int,int /*<<< orphan*/ *) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fnv1a_32__finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fnv1a_32x4__finalize (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_checksum_final(svn_checksum_t **checksum,
                   const svn_checksum_ctx_t *ctx,
                   apr_pool_t *pool)
{
  *checksum = svn_checksum_create(ctx->kind, pool);

  switch (ctx->kind)
    {
      case svn_checksum_md5:
        apr_md5_final((unsigned char *)(*checksum)->digest, ctx->apr_ctx);
        break;

      case svn_checksum_sha1:
        apr_sha1_final((unsigned char *)(*checksum)->digest, ctx->apr_ctx);
        break;

      case svn_checksum_fnv1a_32:
        *(apr_uint32_t *)(*checksum)->digest
          = htonl(svn_fnv1a_32__finalize(ctx->apr_ctx));
        break;

      case svn_checksum_fnv1a_32x4:
        *(apr_uint32_t *)(*checksum)->digest
          = htonl(svn_fnv1a_32x4__finalize(ctx->apr_ctx));
        break;

      default:
        /* We really shouldn't get here, but if we do... */
        return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL, NULL);
    }

  return SVN_NO_ERROR;
}