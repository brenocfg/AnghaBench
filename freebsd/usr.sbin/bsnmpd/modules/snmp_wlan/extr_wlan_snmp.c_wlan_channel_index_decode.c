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
typedef  size_t uint32_t ;
typedef  size_t uint ;
struct asn_oid {size_t len; int* subs; } ;

/* Variables and functions */
 int IFNAMSIZ ; 

__attribute__((used)) static int
wlan_channel_index_decode(const struct asn_oid *oid, uint sub, char *wname,
    uint32_t *cindex)
{
	uint32_t i;
	if (oid->len - sub != oid->subs[sub] + 2 || oid->subs[sub] >= IFNAMSIZ)
		return (-1);

	for (i = 0; i < oid->subs[sub]; i++)
		wname[i] = oid->subs[sub + i + 1];
	wname[i] = '\0';

	*cindex = oid->subs[sub + oid->subs[sub] + 1];

	return (0);
}