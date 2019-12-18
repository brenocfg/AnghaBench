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
typedef  int svn_checksum_kind_t ;
struct TYPE_3__ {int kind; void* apr_ctx; } ;
typedef  TYPE_1__ svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  apr_sha1_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_md5_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 int /*<<< orphan*/  apr_md5_init (void*) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_sha1_init (void*) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 
 void* svn_fnv1a_32__context_create (int /*<<< orphan*/ *) ; 
 void* svn_fnv1a_32x4__context_create (int /*<<< orphan*/ *) ; 

svn_checksum_ctx_t *
svn_checksum_ctx_create(svn_checksum_kind_t kind,
                        apr_pool_t *pool)
{
  svn_checksum_ctx_t *ctx = apr_palloc(pool, sizeof(*ctx));

  ctx->kind = kind;
  switch (kind)
    {
      case svn_checksum_md5:
        ctx->apr_ctx = apr_palloc(pool, sizeof(apr_md5_ctx_t));
        apr_md5_init(ctx->apr_ctx);
        break;

      case svn_checksum_sha1:
        ctx->apr_ctx = apr_palloc(pool, sizeof(apr_sha1_ctx_t));
        apr_sha1_init(ctx->apr_ctx);
        break;

      case svn_checksum_fnv1a_32:
        ctx->apr_ctx = svn_fnv1a_32__context_create(pool);
        break;

      case svn_checksum_fnv1a_32x4:
        ctx->apr_ctx = svn_fnv1a_32x4__context_create(pool);
        break;

      default:
        SVN_ERR_MALFUNCTION_NO_RETURN();
    }

  return ctx;
}