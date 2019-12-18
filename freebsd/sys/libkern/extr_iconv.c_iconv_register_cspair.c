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
struct iconv_cspair {char* cp_to; char* cp_from; void* cp_data; struct iconv_converter_class* cp_dcp; scalar_t__ cp_id; } ;
struct iconv_converter_class {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  M_ICONV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct iconv_cspair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct iconv_cspair*,int) ; 
 int /*<<< orphan*/  cp_link ; 
 int /*<<< orphan*/  iconv_csid ; 
 int /*<<< orphan*/  iconv_cslist ; 
 scalar_t__ iconv_lookupcs (char const*,char const*,int /*<<< orphan*/ *) ; 
 void* iconv_unicode_string ; 
 struct iconv_cspair* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,void*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
iconv_register_cspair(const char *to, const char *from,
	struct iconv_converter_class *dcp, void *data,
	struct iconv_cspair **cspp)
{
	struct iconv_cspair *csp;
	char *cp;
	int csize, ucsto, ucsfrom;

	if (iconv_lookupcs(to, from, NULL) == 0)
		return EEXIST;
	csize = sizeof(*csp);
	ucsto = strcmp(to, iconv_unicode_string) == 0;
	if (!ucsto)
		csize += strlen(to) + 1;
	ucsfrom = strcmp(from, iconv_unicode_string) == 0;
	if (!ucsfrom)
		csize += strlen(from) + 1;
	csp = malloc(csize, M_ICONV, M_WAITOK);
	bzero(csp, csize);
	csp->cp_id = iconv_csid++;
	csp->cp_dcp = dcp;
	cp = (char*)(csp + 1);
	if (!ucsto) {
		strcpy(cp, to);
		csp->cp_to = cp;
		cp += strlen(cp) + 1;
	} else
		csp->cp_to = iconv_unicode_string;
	if (!ucsfrom) {
		strcpy(cp, from);
		csp->cp_from = cp;
	} else
		csp->cp_from = iconv_unicode_string;
	csp->cp_data = data;

	TAILQ_INSERT_TAIL(&iconv_cslist, csp, cp_link);
	*cspp = csp;
	return 0;
}