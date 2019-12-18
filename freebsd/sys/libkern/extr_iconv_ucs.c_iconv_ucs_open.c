#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobj_class {int dummy; } ;
struct iconv_ucs {int convtype; struct iconv_cspair* d_cspf; struct iconv_cspair* d_csp; int /*<<< orphan*/ * ctype; int /*<<< orphan*/ * t_ctp; int /*<<< orphan*/ * f_ctp; } ;
struct iconv_cspair {char* cp_to; char* cp_from; int /*<<< orphan*/  cp_refcount; } ;
struct iconv_converter_class {int dummy; } ;
struct TYPE_2__ {int from_flag; int to_flag; scalar_t__ name; } ;

/* Variables and functions */
 char const* ENCODING_UNICODE ; 
 int /*<<< orphan*/  ENCODING_UTF16 ; 
 char const* ENCODING_UTF8 ; 
 int KICONV_UCS_COMBINE ; 
 int KICONV_UCS_FROM_LE ; 
 int KICONV_UCS_FROM_UTF8 ; 
 int KICONV_UCS_TO_LE ; 
 int KICONV_UCS_TO_UTF8 ; 
 int KICONV_UCS_UCS4 ; 
 char const* KICONV_WCTYPE_NAME ; 
 int /*<<< orphan*/  M_ICONV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  iconv_open (char const*,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ kobj_create (struct kobj_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* unicode_family ; 

__attribute__((used)) static int
iconv_ucs_open(struct iconv_converter_class *dcp,
	struct iconv_cspair *csp, struct iconv_cspair *cspf, void **dpp)
{
	struct iconv_ucs *dp;
	int i;
	const char *from, *to;

	dp = (struct iconv_ucs *)kobj_create((struct kobj_class*)dcp, M_ICONV, M_WAITOK);
	to = csp->cp_to;
	from = cspf ? cspf->cp_from : csp->cp_from;

	dp->convtype = 0;

	if (cspf)
		dp->convtype |= KICONV_UCS_COMBINE;
	for (i = 0; unicode_family[i].name; i++) {
		if (strcasecmp(from, unicode_family[i].name) == 0)
			dp->convtype |= unicode_family[i].from_flag;
		if (strcasecmp(to, unicode_family[i].name) == 0)
			dp->convtype |= unicode_family[i].to_flag;
	}
	if (strcmp(ENCODING_UNICODE, ENCODING_UTF16) == 0)
		dp->convtype |= KICONV_UCS_UCS4;
	else
		dp->convtype &= ~KICONV_UCS_UCS4;

	dp->f_ctp = dp->t_ctp = NULL;
	if (dp->convtype & KICONV_UCS_COMBINE) {
		if ((dp->convtype & KICONV_UCS_FROM_UTF8) == 0 &&
		    (dp->convtype & KICONV_UCS_FROM_LE) == 0) {
			iconv_open(ENCODING_UNICODE, from, &dp->f_ctp);
		}
		if ((dp->convtype & KICONV_UCS_TO_UTF8) == 0 &&
		    (dp->convtype & KICONV_UCS_TO_LE) == 0) {
			iconv_open(to, ENCODING_UNICODE, &dp->t_ctp);
		}
	}

	dp->ctype = NULL;
	if (dp->convtype & (KICONV_UCS_FROM_UTF8 | KICONV_UCS_TO_UTF8))
		iconv_open(KICONV_WCTYPE_NAME, ENCODING_UTF8, &dp->ctype);

	dp->d_csp = csp;
	if (dp->convtype & (KICONV_UCS_FROM_UTF8 | KICONV_UCS_FROM_LE)) {
		if (cspf) {
			dp->d_cspf = cspf;
			cspf->cp_refcount++;
		} else
			csp->cp_refcount++;
	}
	if (dp->convtype & (KICONV_UCS_TO_UTF8 | KICONV_UCS_TO_LE))
		csp->cp_refcount++;
	*dpp = (void*)dp;
	return 0;
}