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
struct TYPE_3__ {int /*<<< orphan*/  const* digest; } ;
typedef  TYPE_1__ svn_x509_certinfo_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;

/* Variables and functions */

const svn_checksum_t *
svn_x509_certinfo_get_digest(const svn_x509_certinfo_t *certinfo)
{
  return certinfo->digest;
}