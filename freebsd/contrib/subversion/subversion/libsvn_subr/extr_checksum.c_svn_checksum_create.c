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
struct TYPE_4__ {scalar_t__ digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* checksum_create_without_digest (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * digest_sizes ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 

svn_checksum_t *
svn_checksum_create(svn_checksum_kind_t kind,
                    apr_pool_t *pool)
{
  svn_checksum_t *checksum;
  apr_size_t digest_size;

  switch (kind)
    {
      case svn_checksum_md5:
      case svn_checksum_sha1:
      case svn_checksum_fnv1a_32:
      case svn_checksum_fnv1a_32x4:
        digest_size = digest_sizes[kind];
        break;

      default:
        return NULL;
    }

  checksum = checksum_create_without_digest(kind, digest_size, pool);
  memset((unsigned char *) checksum->digest, 0, digest_size);
  return checksum;
}