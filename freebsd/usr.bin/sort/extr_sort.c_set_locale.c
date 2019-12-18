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
struct lconv {int /*<<< orphan*/  negative_sign; int /*<<< orphan*/  positive_sign; int /*<<< orphan*/  thousands_sep; int /*<<< orphan*/  decimal_point; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int byte_sort ; 
 int /*<<< orphan*/  conv_mbtowc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getenv (char*) ; 
 int gnusort_numeric_compatibility ; 
 struct lconv* localeconv () ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sort_free (char*) ; 
 char* sort_strdup (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  symbol_decimal_point ; 
 int /*<<< orphan*/  symbol_negative_sign ; 
 int /*<<< orphan*/  symbol_positive_sign ; 
 int /*<<< orphan*/  symbol_thousands_sep ; 

__attribute__((used)) static void
set_locale(void)
{
	struct lconv *lc;
	const char *locale;

	setlocale(LC_ALL, "");

	lc = localeconv();

	if (lc) {
		/* obtain LC_NUMERIC info */
		/* Convert to wide char form */
		conv_mbtowc(&symbol_decimal_point, lc->decimal_point,
		    symbol_decimal_point);
		conv_mbtowc(&symbol_thousands_sep, lc->thousands_sep,
		    symbol_thousands_sep);
		conv_mbtowc(&symbol_positive_sign, lc->positive_sign,
		    symbol_positive_sign);
		conv_mbtowc(&symbol_negative_sign, lc->negative_sign,
		    symbol_negative_sign);
	}

	if (getenv("GNUSORT_NUMERIC_COMPATIBILITY"))
		gnusort_numeric_compatibility = true;

	locale = setlocale(LC_COLLATE, NULL);

	if (locale) {
		char *tmpl;
		const char *cclocale;

		tmpl = sort_strdup(locale);
		cclocale = setlocale(LC_COLLATE, "C");
		if (cclocale && !strcmp(cclocale, tmpl))
			byte_sort = true;
		else {
			const char *pclocale;

			pclocale = setlocale(LC_COLLATE, "POSIX");
			if (pclocale && !strcmp(pclocale, tmpl))
				byte_sort = true;
		}
		setlocale(LC_COLLATE, tmpl);
		sort_free(tmpl);
	}
}