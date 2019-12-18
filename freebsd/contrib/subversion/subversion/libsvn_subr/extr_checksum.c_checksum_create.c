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
typedef  int /*<<< orphan*/  svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIGESTSIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* checksum_create_without_digest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_checksum_t *
checksum_create(svn_checksum_kind_t kind,
                const unsigned char *digest,
                apr_pool_t *pool)
{
  apr_size_t digest_size = DIGESTSIZE(kind);
  svn_checksum_t *checksum = checksum_create_without_digest(kind, digest_size,
                                                            pool);
  memcpy((unsigned char *)checksum->digest, digest, digest_size);
  return checksum;
}