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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL ; 
 char* def ; 
 int /*<<< orphan*/  get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  show_rev (int /*<<< orphan*/ ,struct object_id*,char const*) ; 

__attribute__((used)) static int show_default(void)
{
	const char *s = def;

	if (s) {
		struct object_id oid;

		def = NULL;
		if (!get_oid(s, &oid)) {
			show_rev(NORMAL, &oid, s);
			return 1;
		}
	}
	return 0;
}