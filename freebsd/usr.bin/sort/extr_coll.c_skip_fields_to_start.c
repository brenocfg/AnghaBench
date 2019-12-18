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
struct bwstring {int dummy; } ;
struct TYPE_2__ {scalar_t__ field_sep; int /*<<< orphan*/  tflag; } ;

/* Variables and functions */
 size_t BWSLEN (struct bwstring const*) ; 
 scalar_t__ BWS_GET (struct bwstring const*,size_t) ; 
 int iswblank (scalar_t__) ; 
 TYPE_1__ sort_opts_vals ; 

__attribute__((used)) static size_t
skip_fields_to_start(const struct bwstring *s, size_t fields, bool *empty_field)
{

	if (fields < 2) {
		if (BWSLEN(s) == 0)
			*empty_field = true;
		return (0);
	} else if (!(sort_opts_vals.tflag)) {
		size_t cpos = 0;
		bool pb = true;

		while (cpos < BWSLEN(s)) {
			bool isblank;

			isblank = iswblank(BWS_GET(s, cpos));

			if (isblank && !pb) {
				--fields;
				if (fields <= 1)
					return (cpos);
			}
			pb = isblank;
			++cpos;
		}
		if (fields > 1)
			*empty_field = true;
		return (cpos);
	} else {
		size_t cpos = 0;

		while (cpos < BWSLEN(s)) {
			if (BWS_GET(s,cpos) == (wchar_t)sort_opts_vals.field_sep) {
				--fields;
				if (fields <= 1)
					return (cpos + 1);
			}
			++cpos;
		}
		if (fields > 1)
			*empty_field = true;
		return (cpos);
	}
}