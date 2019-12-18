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
 scalar_t__ asterchar (char const) ; 
 scalar_t__ periodchar (char const) ; 
 int res_hnok (char const*) ; 

int
res_ownok(const char *dn) {
	if (asterchar(dn[0])) {
		if (periodchar(dn[1]))
			return (res_hnok(dn+2));
		if (dn[1] == '\0')
			return (1);
	}
	return (res_hnok(dn));
}