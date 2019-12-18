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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int kind; int /*<<< orphan*/  apr_ctx; } ;
typedef  TYPE_1__ svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  apr_sha1_ctx_t ;
typedef  int /*<<< orphan*/  apr_md5_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_md5_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_sha1_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 
 int /*<<< orphan*/  svn_fnv1a_32__context_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fnv1a_32x4__context_reset (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_checksum_ctx_reset(svn_checksum_ctx_t *ctx)
{
  switch (ctx->kind)
    {
      case svn_checksum_md5:
        memset(ctx->apr_ctx, 0, sizeof(apr_md5_ctx_t));
        apr_md5_init(ctx->apr_ctx);
        break;

      case svn_checksum_sha1:
        memset(ctx->apr_ctx, 0, sizeof(apr_sha1_ctx_t));
        apr_sha1_init(ctx->apr_ctx);
        break;

      case svn_checksum_fnv1a_32:
        svn_fnv1a_32__context_reset(ctx->apr_ctx);
        break;

      case svn_checksum_fnv1a_32x4:
        svn_fnv1a_32x4__context_reset(ctx->apr_ctx);
        break;

      default:
        SVN_ERR_MALFUNCTION();
    }

  return SVN_NO_ERROR;
}