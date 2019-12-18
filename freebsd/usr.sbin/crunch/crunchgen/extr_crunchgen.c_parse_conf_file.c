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

/* Variables and functions */
 int /*<<< orphan*/  cachename ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infilename ; 
 scalar_t__ is_nonempty_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_one_file (int /*<<< orphan*/ ) ; 
 scalar_t__ readcache ; 
 int reading_cache ; 

void
parse_conf_file(void)
{
	if (!is_nonempty_file(infilename))
		errx(1, "fatal: input file \"%s\" not found", infilename);

	parse_one_file(infilename);
	if (readcache && is_nonempty_file(cachename)) {
		reading_cache = 1;
		parse_one_file(cachename);
	}
}