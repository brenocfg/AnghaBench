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
typedef  int wchar_t ;
struct test {char* locale; char* data; size_t wclen; size_t* mblen; } ;
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (size_t,int,char*,size_t,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_STREQ (char*,char*) ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int MB_LEN_MAX ; 
 char TC_WCRTOMB_ST ; 
 char TC_WCTOMB ; 
 int VIS_OCTAL ; 
 int VIS_WHITE ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 size_t mbsrtowcs (int*,char const**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strvis (char*,char*,int) ; 
 size_t wcrtomb (char*,int,int /*<<< orphan*/ *) ; 
 size_t wctomb (char*,int) ; 

__attribute__((used)) static void
h_wctomb(const struct test *t, char tc)
{
	wchar_t wcs[16 + 2];
	char buf[128];
	char cs[MB_LEN_MAX];
	const char *pcs;
	char *str;
	mbstate_t st;
	mbstate_t *stp = NULL;
	size_t sz, ret, i;

	ATF_REQUIRE_STREQ(setlocale(LC_ALL, "C"), "C");
#ifdef __NetBSD__
	ATF_REQUIRE(setlocale(LC_CTYPE, t->locale) != NULL);
#else
	if (setlocale(LC_CTYPE, t->locale) == NULL) {
		fprintf(stderr, "Locale %s not found.\n", t->locale);
		return;
	}
#endif

	(void)strvis(buf, t->data, VIS_WHITE | VIS_OCTAL);
	(void)printf("Checking sequence: \"%s\"\n", buf);

	ATF_REQUIRE((str = setlocale(LC_ALL, NULL)) != NULL);
	(void)printf("Using locale: %s\n", str);

	if (tc == TC_WCRTOMB_ST) {
		(void)memset(&st, 0, sizeof(st));
		stp = &st;
	}

	wcs[t->wclen] = L'X'; /* poison */
	pcs = t->data;
	sz = mbsrtowcs(wcs, &pcs, t->wclen + 2, NULL);
	ATF_REQUIRE_EQ_MSG(sz, t->wclen, "mbsrtowcs() returned: "
		"%zu, expected: %zu", sz, t->wclen);
	ATF_REQUIRE_EQ(wcs[t->wclen], 0);

	for (i = 0; i < t->wclen + 1; i++) {
		if (tc == TC_WCTOMB)
			ret = wctomb(cs, wcs[i]);
		else
			ret = wcrtomb(cs, wcs[i], stp);

		if (ret == t->mblen[i])
			continue;

		(void)printf("At position %zd:\n", i);
		(void)printf("  expected: %zd\n", t->mblen[i]);
		(void)printf("  got     : %zd\n", ret);
		atf_tc_fail("Test failed");
		/* NOTREACHED */
	}

	(void)printf("Ok.\n");
}