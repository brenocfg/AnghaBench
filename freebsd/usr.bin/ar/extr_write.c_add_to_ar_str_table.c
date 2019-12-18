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
struct bsdar {char* as; int as_cap; size_t as_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int _INIT_AS_CAP ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 char* malloc (int) ; 
 char* realloc (char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void
add_to_ar_str_table(struct bsdar *bsdar, const char *name)
{

	if (bsdar->as == NULL) {
		bsdar->as_cap = _INIT_AS_CAP;
		bsdar->as_sz = 0;
		if ((bsdar->as = malloc(bsdar->as_cap)) == NULL)
			bsdar_errc(bsdar, EX_SOFTWARE, errno, "malloc failed");
	}

	/*
	 * The space required for holding one member name in as table includes:
	 * strlen(name) + (1 for '/') + (1 for '\n') + (possibly 1 for padding).
	 */
	while (bsdar->as_sz + strlen(name) + 3 > bsdar->as_cap) {
		bsdar->as_cap *= 2;
		bsdar->as = realloc(bsdar->as, bsdar->as_cap);
		if (bsdar->as == NULL)
			bsdar_errc(bsdar, EX_SOFTWARE, errno, "realloc failed");
	}
	strncpy(&bsdar->as[bsdar->as_sz], name, strlen(name));
	bsdar->as_sz += strlen(name);
	bsdar->as[bsdar->as_sz++] = '/';
	bsdar->as[bsdar->as_sz++] = '\n';
}