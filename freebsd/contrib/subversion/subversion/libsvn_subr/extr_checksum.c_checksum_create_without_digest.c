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
struct TYPE_4__ {unsigned char* digest; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_kind_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static svn_checksum_t *
checksum_create_without_digest(svn_checksum_kind_t kind,
                               apr_size_t digest_size,
                               apr_pool_t *pool)
{
  /* Use apr_palloc() instead of apr_pcalloc() so that the digest
   * contents are only set once by the caller. */
  svn_checksum_t *checksum = apr_palloc(pool, sizeof(*checksum) + digest_size);
  checksum->digest = (unsigned char *)checksum + sizeof(*checksum);
  checksum->kind = kind;
  return checksum;
}