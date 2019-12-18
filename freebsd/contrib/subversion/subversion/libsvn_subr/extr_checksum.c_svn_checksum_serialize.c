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
struct TYPE_4__ {size_t kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char const* apr_pstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ckind_str ; 
 size_t svn_checksum_fnv1a_32x4 ; 
 size_t svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

const char *
svn_checksum_serialize(const svn_checksum_t *checksum,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT_NO_RETURN(checksum->kind >= svn_checksum_md5
                           || checksum->kind <= svn_checksum_fnv1a_32x4);
  return apr_pstrcat(result_pool,
                     ckind_str[checksum->kind],
                     svn_checksum_to_cstring(checksum, scratch_pool),
                     SVN_VA_NULL);
}