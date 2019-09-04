#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct TYPE_4__ {char const* path; int pathlen; TYPE_1__ oid; } ;
struct traverse_info {int pathlen; struct traverse_info* prev; TYPE_2__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  memset (struct traverse_info*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

void setup_traverse_info(struct traverse_info *info, const char *base)
{
	int pathlen = strlen(base);
	static struct traverse_info dummy;

	memset(info, 0, sizeof(*info));
	if (pathlen && base[pathlen-1] == '/')
		pathlen--;
	info->pathlen = pathlen ? pathlen + 1 : 0;
	info->name.path = base;
	info->name.pathlen = pathlen;
	if (pathlen) {
		hashcpy(info->name.oid.hash, (const unsigned char *)base + pathlen + 1);
		info->prev = &dummy;
	}
}