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
struct TYPE_3__ {int kind; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * digest_sizes ; 
 char const* svn__digest_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 

const char *
svn_checksum_to_cstring(const svn_checksum_t *checksum,
                        apr_pool_t *pool)
{
  if (checksum == NULL)
    return NULL;

  switch (checksum->kind)
    {
      case svn_checksum_md5:
      case svn_checksum_sha1:
      case svn_checksum_fnv1a_32:
      case svn_checksum_fnv1a_32x4:
        return svn__digest_to_cstring(checksum->digest,
                                      digest_sizes[checksum->kind],
                                      pool);

      default:
        /* We really shouldn't get here, but if we do... */
        return NULL;
    }
}