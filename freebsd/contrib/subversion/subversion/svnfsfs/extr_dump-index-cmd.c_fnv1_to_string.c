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
struct TYPE_3__ {unsigned char const* digest; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_fnv1a_32 ; 
 char const* svn_checksum_to_cstring_display (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
fnv1_to_string(apr_uint32_t fnv1,
               apr_pool_t *pool)
{
  /* Construct a checksum object containing FNV1. */
  svn_checksum_t checksum = { NULL, svn_checksum_fnv1a_32 };
  apr_uint32_t digest = htonl(fnv1);
  checksum.digest = (const unsigned char *)&digest;

  /* Convert the digest to hex. */
  return svn_checksum_to_cstring_display(&checksum, pool);
}