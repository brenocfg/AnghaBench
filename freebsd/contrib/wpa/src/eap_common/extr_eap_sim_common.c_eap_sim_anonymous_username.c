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
typedef  char u8 ;

/* Variables and functions */
 scalar_t__ os_memcmp (char const*,char const*,size_t) ; 
 size_t os_strlen (char const*) ; 

int eap_sim_anonymous_username(const u8 *id, size_t id_len)
{
	static const char *anonymous_id_prefix = "anonymous@";
	size_t anonymous_id_len = os_strlen(anonymous_id_prefix);

	if (id_len > anonymous_id_len &&
	    os_memcmp(id, anonymous_id_prefix, anonymous_id_len) == 0)
		return 1; /* 'anonymous@realm' */

	if (id_len > 1 && id[0] == '@')
		return 1; /* '@realm' */

	return 0;
}