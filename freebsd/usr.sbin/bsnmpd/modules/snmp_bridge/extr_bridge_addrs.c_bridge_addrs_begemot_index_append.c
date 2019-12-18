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
typedef  int uint ;
struct tp_entry {int* tp_addr; int /*<<< orphan*/  sysindex; } ;
struct asn_oid {int* subs; scalar_t__ len; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 char* bridge_if_find_name (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
bridge_addrs_begemot_index_append(struct asn_oid *oid, uint sub,
	const struct tp_entry *te)
{
	uint i, n_len;
	const char *b_name;

	if ((b_name = bridge_if_find_name(te->sysindex)) == NULL)
		return (-1);

	n_len = strlen(b_name);
	oid->len = sub++;
	oid->subs[oid->len++] = n_len;

	for (i = 1; i <= n_len; i++)
		oid->subs[oid->len++] = b_name[i - 1];

	oid->subs[oid->len++] = ETHER_ADDR_LEN;
	for (i = 1 ; i <= ETHER_ADDR_LEN; i++)
		oid->subs[oid->len++] = te->tp_addr[i - 1];

	return (0);
}