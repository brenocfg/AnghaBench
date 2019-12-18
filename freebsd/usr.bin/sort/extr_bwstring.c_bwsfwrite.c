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
typedef  int wchar_t ;
struct TYPE_2__ {char* cstr; int* wstr; } ;
struct bwstring {size_t len; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BWSLEN (struct bwstring*) ; 
 int MB_CUR_MAX ; 
 int btowc (char) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int fwprintf (int /*<<< orphan*/ *,char*,...) ; 
 int fwrite (char*,size_t,int,int /*<<< orphan*/ *) ; 

size_t
bwsfwrite(struct bwstring *bws, FILE *f, bool zero_ended)
{

	if (MB_CUR_MAX == 1) {
		size_t len = bws->len;

		if (!zero_ended) {
			bws->data.cstr[len] = '\n';

			if (fwrite(bws->data.cstr, len + 1, 1, f) < 1)
				err(2, NULL);

			bws->data.cstr[len] = '\0';
		} else if (fwrite(bws->data.cstr, len + 1, 1, f) < 1)
			err(2, NULL);

		return (len + 1);

	} else {
		wchar_t eols;
		size_t printed = 0;

		eols = zero_ended ? btowc('\0') : btowc('\n');

		while (printed < BWSLEN(bws)) {
			const wchar_t *s = bws->data.wstr + printed;

			if (*s == L'\0') {
				int nums;

				nums = fwprintf(f, L"%lc", *s);

				if (nums != 1)
					err(2, NULL);
				++printed;
			} else {
				int nums;

				nums = fwprintf(f, L"%ls", s);

				if (nums < 1)
					err(2, NULL);
				printed += nums;
			}
		}
		fwprintf(f, L"%lc", eols);
		return (printed + 1);
	}
}