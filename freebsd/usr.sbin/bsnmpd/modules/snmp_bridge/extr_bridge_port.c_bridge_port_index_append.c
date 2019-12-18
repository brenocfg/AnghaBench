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
typedef  size_t uint ;
struct bridge_port {char port_no; int /*<<< orphan*/  sysindex; } ;
struct asn_oid {size_t len; size_t* subs; } ;

/* Variables and functions */
 char* bridge_if_find_name (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
bridge_port_index_append(struct asn_oid *oid, uint sub,
	const struct bridge_port *bp)
{
	uint i;
	const char *b_name;

	if ((b_name = bridge_if_find_name(bp->sysindex)) == NULL)
		return (-1);

	oid->len = sub + strlen(b_name) + 1 + 1;
	oid->subs[sub] = strlen(b_name);

	for (i = 1; i <= strlen(b_name); i++)
		oid->subs[sub + i] = b_name[i - 1];

	oid->subs[sub + i] = bp->port_no;

	return (0);
}