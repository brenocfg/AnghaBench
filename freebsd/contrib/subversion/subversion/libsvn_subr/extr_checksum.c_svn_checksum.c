#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {scalar_t__ digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_sha1_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_md5 (unsigned char*,void const*,scalar_t__) ; 
 int /*<<< orphan*/  apr_sha1_final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_sha1_update (int /*<<< orphan*/ *,void const*,unsigned int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn__fnv1a_32 (void const*,scalar_t__) ; 
 int /*<<< orphan*/  svn__fnv1a_32x4 (void const*,scalar_t__) ; 
 TYPE_1__* svn_checksum_create (int,int /*<<< orphan*/ *) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_kind (int) ; 

svn_error_t *
svn_checksum(svn_checksum_t **checksum,
             svn_checksum_kind_t kind,
             const void *data,
             apr_size_t len,
             apr_pool_t *pool)
{
  apr_sha1_ctx_t sha1_ctx;

  SVN_ERR(validate_kind(kind));
  *checksum = svn_checksum_create(kind, pool);

  switch (kind)
    {
      case svn_checksum_md5:
        apr_md5((unsigned char *)(*checksum)->digest, data, len);
        break;

      case svn_checksum_sha1:
        apr_sha1_init(&sha1_ctx);
        apr_sha1_update(&sha1_ctx, data, (unsigned int)len);
        apr_sha1_final((unsigned char *)(*checksum)->digest, &sha1_ctx);
        break;

      case svn_checksum_fnv1a_32:
        *(apr_uint32_t *)(*checksum)->digest
          = htonl(svn__fnv1a_32(data, len));
        break;

      case svn_checksum_fnv1a_32x4:
        *(apr_uint32_t *)(*checksum)->digest
          = htonl(svn__fnv1a_32x4(data, len));
        break;

      default:
        /* We really shouldn't get here, but if we do... */
        return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL, NULL);
    }

  return SVN_NO_ERROR;
}