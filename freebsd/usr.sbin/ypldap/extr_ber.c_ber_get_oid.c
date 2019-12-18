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
typedef  int u_int8_t ;
struct ber_oid {int* bo_id; size_t bo_n; } ;
struct ber_element {scalar_t__ be_encoding; int* be_val; size_t be_len; } ;

/* Variables and functions */
 size_t BER_MAX_OID_LEN ; 
 scalar_t__ BER_TYPE_OBJECT ; 
 int /*<<< orphan*/  bzero (struct ber_oid*,int) ; 

int
ber_get_oid(struct ber_element *elm, struct ber_oid *o)
{
	u_int8_t	*buf;
	size_t		 len, i = 0, j = 0;

	if (elm->be_encoding != BER_TYPE_OBJECT)
		return (-1);

	buf = elm->be_val;
	len = elm->be_len;

	if (!buf[i])
		return (-1);

	bzero(o, sizeof(*o));
	o->bo_id[j++] = buf[i] / 40;
	o->bo_id[j++] = buf[i++] % 40;
	for (; i < len && j < BER_MAX_OID_LEN; i++) {
		o->bo_id[j] = (o->bo_id[j] << 7) + (buf[i] & ~0x80);
		if (buf[i] & 0x80)
			continue;
		j++;
	}
	o->bo_n = j;

	return (0);
}