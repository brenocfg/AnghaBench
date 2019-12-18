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
typedef  int /*<<< orphan*/  u8 ;
struct p2ps_advertisement {scalar_t__ svc_info; } ;

/* Variables and functions */
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 size_t os_strlen (scalar_t__) ; 

__attribute__((used)) static int find_p2ps_substr(struct p2ps_advertisement *adv_data,
			    const u8 *needle, size_t needle_len)
{
	const u8 *haystack = (const u8 *) adv_data->svc_info;
	size_t haystack_len, i;

	/* Allow search term to be empty */
	if (!needle || !needle_len)
		return 1;

	if (!haystack)
		return 0;

	haystack_len = os_strlen(adv_data->svc_info);
	for (i = 0; i < haystack_len; i++) {
		if (haystack_len - i < needle_len)
			break;
		if (os_memcmp(haystack + i, needle, needle_len) == 0)
			return 1;
	}

	return 0;
}