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
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 int /*<<< orphan*/ * checksum_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * empty_string_digests ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 

svn_checksum_t *
svn_checksum_empty_checksum(svn_checksum_kind_t kind,
                            apr_pool_t *pool)
{
  switch (kind)
    {
      case svn_checksum_md5:
      case svn_checksum_sha1:
      case svn_checksum_fnv1a_32:
      case svn_checksum_fnv1a_32x4:
        return checksum_create(kind, empty_string_digests[kind], pool);

      default:
        /* We really shouldn't get here, but if we do... */
        SVN_ERR_MALFUNCTION_NO_RETURN();
    }
}