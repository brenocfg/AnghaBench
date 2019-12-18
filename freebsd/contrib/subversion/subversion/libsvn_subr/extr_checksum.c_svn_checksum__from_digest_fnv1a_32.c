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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * checksum_create (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_fnv1a_32 ; 

svn_checksum_t *
svn_checksum__from_digest_fnv1a_32(const unsigned char *digest,
                                   apr_pool_t *result_pool)
{
  return checksum_create(svn_checksum_fnv1a_32, digest, result_pool);
}