#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct xlocale_collate {TYPE_3__* info; TYPE_1__* char_pri_table; scalar_t__ __collate_load_error; } ;
typedef  TYPE_4__* locale_t ;
typedef  int int32_t ;
struct TYPE_12__ {int* pri; } ;
struct TYPE_15__ {TYPE_2__ pri; } ;
typedef  TYPE_5__ collate_large_t ;
struct TYPE_16__ {int* pri; } ;
typedef  TYPE_6__ collate_chain_t ;
struct TYPE_14__ {scalar_t__* components; } ;
struct TYPE_13__ {scalar_t__ large_count; scalar_t__ chain_count; } ;
struct TYPE_11__ {int* pri; } ;

/* Variables and functions */
 size_t COLLATE_STR_LEN ; 
 int /*<<< orphan*/  FIX_LOCALE (TYPE_4__*) ; 
 int const UCHAR_MAX ; 
 size_t XLC_COLLATE ; 
 TYPE_6__* chainsearch (struct xlocale_collate*,int*,int*) ; 
 TYPE_5__* largesearch (struct xlocale_collate*,int const) ; 
 int /*<<< orphan*/  wcsncpy (int*,int const*,size_t) ; 

int
__collate_equiv_value(locale_t locale, const wchar_t *str, size_t len)
{
	int32_t e;

	if (len < 1 || len >= COLLATE_STR_LEN)
		return (-1);

	FIX_LOCALE(locale);
	struct xlocale_collate *table =
		(struct xlocale_collate*)locale->components[XLC_COLLATE];

	if (table->__collate_load_error)
		return ((len == 1 && *str <= UCHAR_MAX) ? *str : -1);

	if (len == 1) {
		e = -1;
		if (*str <= UCHAR_MAX)
			e = table->char_pri_table[*str].pri[0];
		else if (table->info->large_count > 0) {
			collate_large_t *match_large;
			match_large = largesearch(table, *str);
			if (match_large)
				e = match_large->pri.pri[0];
		}
		if (e == 0)
			return (1);
		return (e > 0 ? e : 0);
	}
	if (table->info->chain_count > 0) {
		wchar_t name[COLLATE_STR_LEN];
		collate_chain_t *match_chain;
		int clen;

		wcsncpy (name, str, len);
		name[len] = 0;
		match_chain = chainsearch(table, name, &clen);
		if (match_chain) {
			e = match_chain->pri[0];
			if (e == 0)
				return (1);
			return (e < 0 ? -e : e);
		}
	}
	return (0);
}