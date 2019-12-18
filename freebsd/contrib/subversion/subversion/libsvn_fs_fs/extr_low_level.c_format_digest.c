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
struct TYPE_3__ {unsigned char const* digest; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* svn_checksum_to_cstring_display (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
format_digest(const unsigned char *digest,
              svn_checksum_kind_t kind,
              apr_pool_t *result_pool)
{
  svn_checksum_t checksum;
  checksum.digest = digest;
  checksum.kind = kind;

  return svn_checksum_to_cstring_display(&checksum, result_pool);
}