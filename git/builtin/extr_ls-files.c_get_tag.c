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
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_FSMONITOR_VALID ; 
 int CE_VALID ; 
 scalar_t__ isalpha (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ show_fsmonitor_bit ; 
 scalar_t__ show_valid_bit ; 
 char tolower (char const) ; 

__attribute__((used)) static const char *get_tag(const struct cache_entry *ce, const char *tag)
{
	static char alttag[4];

	if (tag && *tag && ((show_valid_bit && (ce->ce_flags & CE_VALID)) ||
		(show_fsmonitor_bit && (ce->ce_flags & CE_FSMONITOR_VALID)))) {
		memcpy(alttag, tag, 3);

		if (isalpha(tag[0])) {
			alttag[0] = tolower(tag[0]);
		} else if (tag[0] == '?') {
			alttag[0] = '!';
		} else {
			alttag[0] = 'v';
			alttag[1] = tag[0];
			alttag[2] = ' ';
			alttag[3] = 0;
		}

		tag = alttag;
	}

	return tag;
}