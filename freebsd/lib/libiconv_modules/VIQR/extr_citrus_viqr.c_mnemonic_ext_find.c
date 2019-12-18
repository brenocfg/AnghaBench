#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
struct TYPE_3__ {scalar_t__ value; char const* name; } ;
typedef  TYPE_1__ mnemonic_def_t ;

/* Variables and functions */

__attribute__((used)) static const char *
mnemonic_ext_find(wchar_t wc, const mnemonic_def_t *head, size_t n)
{
	const mnemonic_def_t *mid;

	for (; n > 0; n >>= 1) {
		mid = head + (n >> 1);
		if (mid->value == wc)
			return (mid->name);
		else if (mid->value < wc) {
			head = mid + 1;
			--n;
		}
	}
	return (NULL);
}