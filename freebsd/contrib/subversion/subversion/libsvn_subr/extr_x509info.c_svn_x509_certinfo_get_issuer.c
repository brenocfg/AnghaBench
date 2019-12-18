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
struct TYPE_3__ {int /*<<< orphan*/  issuer; } ;
typedef  TYPE_1__ svn_x509_certinfo_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* get_dn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_x509_certinfo_get_issuer(const svn_x509_certinfo_t *certinfo,
                             apr_pool_t *result_pool)
{
  return get_dn(certinfo->issuer, result_pool);
}