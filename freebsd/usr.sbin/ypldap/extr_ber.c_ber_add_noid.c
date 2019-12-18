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
struct ber_oid {int bo_n; int /*<<< orphan*/  bo_id; } ;
struct ber_element {int dummy; } ;

/* Variables and functions */
 int BER_MAX_OID_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct ber_element* ber_add_oid (struct ber_element*,struct ber_oid*) ; 

struct ber_element *
ber_add_noid(struct ber_element *prev, struct ber_oid *o, int n)
{
	struct ber_oid		 no;

	if (n > BER_MAX_OID_LEN)
		return (NULL);
	no.bo_n = n;
	bcopy(&o->bo_id, &no.bo_id, sizeof(no.bo_id));

	return (ber_add_oid(prev, &no));
}