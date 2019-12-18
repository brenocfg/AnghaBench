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
typedef  scalar_t__ wchar_t ;
struct key_specs {size_t f2; scalar_t__ c2; int /*<<< orphan*/  pos2b; } ;
struct bwstring {int dummy; } ;
struct TYPE_2__ {scalar_t__ field_sep; scalar_t__ tflag; } ;

/* Variables and functions */
 size_t BWSLEN (struct bwstring const*) ; 
 scalar_t__ BWS_GET (struct bwstring const*,size_t) ; 
 size_t skip_cols_to_start (struct bwstring const*,scalar_t__,size_t,int /*<<< orphan*/ ,int*) ; 
 size_t skip_fields_to_start (struct bwstring const*,size_t,int*) ; 
 TYPE_1__ sort_opts_vals ; 

__attribute__((used)) static size_t
find_field_end(const struct bwstring *s, struct key_specs *ks)
{
	size_t f2, next_field_start, pos_end;
	bool empty_field, empty_key;

	empty_field = false;
	empty_key = false;
	f2 = ks->f2;

	if (f2 == 0)
		return (BWSLEN(s) + 1);
	else {
		if (ks->c2 == 0) {
			next_field_start = skip_fields_to_start(s, f2 + 1,
			    &empty_field);
			if ((next_field_start > 0) && sort_opts_vals.tflag &&
			    ((wchar_t)sort_opts_vals.field_sep == BWS_GET(s,
			    next_field_start - 1)))
				--next_field_start;
		} else
			next_field_start = skip_fields_to_start(s, f2,
			    &empty_field);
	}

	if (empty_field || (next_field_start >= BWSLEN(s)))
		return (BWSLEN(s) + 1);

	if (ks->c2) {
		pos_end = skip_cols_to_start(s, ks->c2, next_field_start,
		    ks->pos2b, &empty_key);
		if (pos_end < BWSLEN(s))
			++pos_end;
	} else
		pos_end = next_field_start;

	return (pos_end);
}