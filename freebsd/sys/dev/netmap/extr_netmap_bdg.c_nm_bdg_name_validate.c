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
 int IFNAMSIZ ; 
 int NM_BDG_IFNAMSIZ ; 
 int /*<<< orphan*/  nm_is_id_char (char const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
nm_bdg_name_validate(const char *name, size_t prefixlen)
{
	int colon_pos = -1;
	int i;

	if (!name || strlen(name) < prefixlen) {
		return -1;
	}

	for (i = 0; i < NM_BDG_IFNAMSIZ && name[i]; i++) {
		if (name[i] == ':') {
			colon_pos = i;
			break;
		} else if (!nm_is_id_char(name[i])) {
			return -1;
		}
	}

	if (strlen(name) - colon_pos > IFNAMSIZ) {
		/* interface name too long */
		return -1;
	}

	return colon_pos;
}