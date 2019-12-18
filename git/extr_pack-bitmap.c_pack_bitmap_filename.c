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
struct packed_git {int /*<<< orphan*/  pack_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  strip_suffix (int /*<<< orphan*/ ,char*,size_t*) ; 
 char* xstrfmt (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *pack_bitmap_filename(struct packed_git *p)
{
	size_t len;

	if (!strip_suffix(p->pack_name, ".pack", &len))
		BUG("pack_name does not end in .pack");
	return xstrfmt("%.*s.bitmap", (int)len, p->pack_name);
}