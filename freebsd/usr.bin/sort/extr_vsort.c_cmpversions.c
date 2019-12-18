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
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ bwstring_iterator ;

/* Variables and functions */
 scalar_t__ bws_get_iter_value (scalar_t__) ; 
 scalar_t__ bws_iterator_inc (scalar_t__,int) ; 
 int cmp_chars (scalar_t__,scalar_t__) ; 
 scalar_t__ isdigit_clocale (scalar_t__) ; 

__attribute__((used)) static int
cmpversions(bwstring_iterator si1, bwstring_iterator se1,
    bwstring_iterator si2, bwstring_iterator se2)
{
	int cmp, diff;

	while ((si1 < se1) || (si2 < se2)) {
		diff = 0;

		while (((si1 < se1) &&
		    !isdigit_clocale(bws_get_iter_value(si1))) ||
		    ((si2 < se2) && !isdigit_clocale(bws_get_iter_value(si2)))) {
			wchar_t c1, c2;

			c1 = (si1 < se1) ? bws_get_iter_value(si1) : 0;
			c2 = (si2 < se2) ? bws_get_iter_value(si2) : 0;

			cmp = cmp_chars(c1, c2);
			if (cmp)
				return (cmp);

			if (si1 < se1)
				si1 = bws_iterator_inc(si1, 1);
			if (si2 < se2)
				si2 = bws_iterator_inc(si2, 1);
		}

		while (bws_get_iter_value(si1) == L'0')
			si1 = bws_iterator_inc(si1, 1);

		while (bws_get_iter_value(si2) == L'0')
			si2 = bws_iterator_inc(si2, 1);

		while (isdigit_clocale(bws_get_iter_value(si1)) &&
		    isdigit_clocale(bws_get_iter_value(si2))) {
			if (!diff)
				diff = ((int)bws_get_iter_value(si1) -
				    (int)bws_get_iter_value(si2));
			si1 = bws_iterator_inc(si1, 1);
			si2 = bws_iterator_inc(si2, 1);
		}

		if (isdigit_clocale(bws_get_iter_value(si1)))
			return (1);

		if (isdigit_clocale(bws_get_iter_value(si2)))
			return (-1);

		if (diff)
			return (diff);
	}

	return (0);
}