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
struct blame_origin {TYPE_2__* commit; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 char* find_unique_abbrev (int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int update_auto_abbrev(int auto_abbrev, struct blame_origin *suspect)
{
	const char *uniq = find_unique_abbrev(&suspect->commit->object.oid,
					      auto_abbrev);
	int len = strlen(uniq);
	if (auto_abbrev < len)
		return len;
	return auto_abbrev;
}