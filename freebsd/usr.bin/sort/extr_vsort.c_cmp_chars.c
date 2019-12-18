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

/* Variables and functions */
 scalar_t__ isalpha_clocale (int) ; 
 scalar_t__ isdigit_clocale (int) ; 

__attribute__((used)) static inline int
cmp_chars(wchar_t c1, wchar_t c2)
{

	if (c1 == c2)
		return (0);

	if (c1 == L'~')
		return (-1);
	if (c2 == L'~')
		return (+1);

	if (isdigit_clocale(c1) || !c1)
		return ((isdigit_clocale(c2) || !c2) ? 0 : -1);

	if (isdigit_clocale(c2) || !c2)
		return (+1);

	if (isalpha_clocale(c1))
		return ((isalpha_clocale(c2)) ? ((int) c1 - (int) c2) : -1);

	if (isalpha_clocale(c2))
		return (+1);

	return ((int) c1 - (int) c2);
}