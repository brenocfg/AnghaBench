#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int iv; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ucl_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_BOOLEAN ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static inline bool
ucl_maybe_parse_boolean (ucl_object_t *obj, const unsigned char *start, size_t len)
{
	const char *p = (const char *)start;
	bool ret = false, val = false;

	if (len == 5) {
		if ((p[0] == 'f' || p[0] == 'F') && strncasecmp (p, "false", 5) == 0) {
			ret = true;
			val = false;
		}
	}
	else if (len == 4) {
		if ((p[0] == 't' || p[0] == 'T') && strncasecmp (p, "true", 4) == 0) {
			ret = true;
			val = true;
		}
	}
	else if (len == 3) {
		if ((p[0] == 'y' || p[0] == 'Y') && strncasecmp (p, "yes", 3) == 0) {
			ret = true;
			val = true;
		}
		else if ((p[0] == 'o' || p[0] == 'O') && strncasecmp (p, "off", 3) == 0) {
			ret = true;
			val = false;
		}
	}
	else if (len == 2) {
		if ((p[0] == 'n' || p[0] == 'N') && strncasecmp (p, "no", 2) == 0) {
			ret = true;
			val = false;
		}
		else if ((p[0] == 'o' || p[0] == 'O') && strncasecmp (p, "on", 2) == 0) {
			ret = true;
			val = true;
		}
	}

	if (ret && obj != NULL) {
		obj->type = UCL_BOOLEAN;
		obj->value.iv = val;
	}

	return ret;
}