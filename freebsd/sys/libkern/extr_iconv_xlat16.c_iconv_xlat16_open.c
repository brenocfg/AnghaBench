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
typedef  int /*<<< orphan*/  uint32_t ;
struct kobj_class {int dummy; } ;
struct iconv_xlat16 {struct iconv_cspair* d_csp; struct iconv_xlat16* t_ctp; struct iconv_xlat16* f_ctp; int /*<<< orphan*/ ** d_table; } ;
struct iconv_cspair {int /*<<< orphan*/  cp_refcount; int /*<<< orphan*/  cp_to; int /*<<< orphan*/  cp_from; scalar_t__ cp_data; } ;
struct iconv_converter_class {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KICONV_WCTYPE_NAME ; 
 int /*<<< orphan*/  M_ICONV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ iconv_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iconv_xlat16**) ; 
 scalar_t__ kobj_create (struct kobj_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iconv_xlat16_open(struct iconv_converter_class *dcp,
	struct iconv_cspair *csp, struct iconv_cspair *cspf, void **dpp)
{
	struct iconv_xlat16 *dp;
	uint32_t *headp, **idxp;
	int i;

	dp = (struct iconv_xlat16 *)kobj_create((struct kobj_class*)dcp, M_ICONV, M_WAITOK);
	headp = (uint32_t *)((caddr_t)csp->cp_data + sizeof(dp->d_table));
	idxp = (uint32_t **)csp->cp_data;
	for (i = 0 ; i < 0x200 ; i++) {
		if (*idxp) {
			dp->d_table[i] = headp;
			headp += 0x80;
		} else {
			dp->d_table[i] = NULL;
		}
		idxp++;
	}

	if (strcmp(csp->cp_to, KICONV_WCTYPE_NAME) != 0) {
		if (iconv_open(KICONV_WCTYPE_NAME, csp->cp_from, &dp->f_ctp) != 0)
			dp->f_ctp = NULL;
		if (iconv_open(KICONV_WCTYPE_NAME, csp->cp_to, &dp->t_ctp) != 0)
			dp->t_ctp = NULL;
	} else {
		dp->f_ctp = dp->t_ctp = dp;
	}

	dp->d_csp = csp;
	csp->cp_refcount++;
	*dpp = (void*)dp;
	return (0);
}