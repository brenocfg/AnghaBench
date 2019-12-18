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
struct bwstring {int dummy; } ;
typedef  int /*<<< orphan*/  bwstring_iterator ;

/* Variables and functions */
 size_t BWSLEN (struct bwstring*) ; 
 int /*<<< orphan*/  bws_begin (struct bwstring*) ; 
 int /*<<< orphan*/  bws_end (struct bwstring*) ; 
 int bws_get_iter_value (int /*<<< orphan*/ ) ; 
 scalar_t__ bws_iterator_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bws_iterator_inc (int /*<<< orphan*/ ,size_t) ; 
 int bwscmp (struct bwstring*,struct bwstring*,int /*<<< orphan*/ ) ; 
 int cmpversions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_suffix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

int
vcmp(struct bwstring *s1, struct bwstring *s2)
{
	bwstring_iterator si1, si2;
	wchar_t c1, c2;
	size_t len1, len2, slen1, slen2;
	int cmp_bytes, cmp_res;

	if (s1 == s2)
		return (0);

	cmp_bytes = bwscmp(s1, s2, 0);
	if (cmp_bytes == 0)
		return (0);

	len1 = slen1 = BWSLEN(s1);
	len2 = slen2 = BWSLEN(s2);

	if (slen1 < 1)
		return (-1);
	if (slen2 < 1)
		return (+1);

	si1 = bws_begin(s1);
	si2 = bws_begin(s2);

	c1 = bws_get_iter_value(si1);
	c2 = bws_get_iter_value(si2);

	if (c1 == L'.' && (slen1 == 1))
		return (-1);

	if (c2 == L'.' && (slen2 == 1))
		return (+1);

	if (slen1 == 2 && c1 == L'.' &&
	    bws_get_iter_value(bws_iterator_inc(si1, 1)) == L'.')
		return (-1);
	if (slen2 == 2 && c2 == L'.' &&
	    bws_get_iter_value(bws_iterator_inc(si2, 1)) == L'.')
		return (+1);

	if (c1 == L'.' && c2 != L'.')
		return (-1);
	if (c1 != L'.' && c2 == L'.')
		return (+1);

	if (c1 == L'.' && c2 == L'.') {
		si1 = bws_iterator_inc(si1, 1);
		si2 = bws_iterator_inc(si2, 1);
	}

	find_suffix(si1, bws_end(s1), &len1);
	find_suffix(si2, bws_end(s2), &len2);

	if ((len1 == len2) && (bws_iterator_cmp(si1, si2, len1) == 0))
		return (cmp_bytes);

	cmp_res = cmpversions(si1, bws_iterator_inc(si1, len1), si2,
	    bws_iterator_inc(si2, len2));

	if (cmp_res == 0)
	  cmp_res = cmp_bytes;

	return (cmp_res);
}