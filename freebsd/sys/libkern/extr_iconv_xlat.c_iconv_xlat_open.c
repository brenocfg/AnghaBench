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
struct kobj_class {int dummy; } ;
struct iconv_xlat {struct iconv_cspair* d_csp; int /*<<< orphan*/  d_table; } ;
struct iconv_cspair {int /*<<< orphan*/  cp_refcount; int /*<<< orphan*/  cp_data; } ;
struct iconv_converter_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ICONV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ kobj_create (struct kobj_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iconv_xlat_open(struct iconv_converter_class *dcp,
	struct iconv_cspair *csp, struct iconv_cspair *cspf, void **dpp)
{
	struct iconv_xlat *dp;

	dp = (struct iconv_xlat *)kobj_create((struct kobj_class*)dcp, M_ICONV, M_WAITOK);
	dp->d_table = csp->cp_data;
	dp->d_csp = csp;
	csp->cp_refcount++;
	*dpp = (void*)dp;
	return 0;
}