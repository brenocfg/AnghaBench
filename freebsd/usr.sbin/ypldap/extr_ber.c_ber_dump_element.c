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
typedef  unsigned long long uint8_t ;
struct ber_element {int be_encoding; int be_len; struct ber_element* be_next; struct ber_element* be_sub; int /*<<< orphan*/  be_val; scalar_t__ be_numeric; } ;
struct ber {int dummy; } ;

/* Variables and functions */
#define  BER_TYPE_BITSTRING 137 
#define  BER_TYPE_BOOLEAN 136 
#define  BER_TYPE_ENUMERATED 135 
#define  BER_TYPE_EOC 134 
#define  BER_TYPE_INTEGER 133 
#define  BER_TYPE_NULL 132 
#define  BER_TYPE_OBJECT 131 
#define  BER_TYPE_OCTETSTRING 130 
#define  BER_TYPE_SEQUENCE 129 
#define  BER_TYPE_SET 128 
 int /*<<< orphan*/  ber_dump_header (struct ber*,struct ber_element*) ; 
 int /*<<< orphan*/  ber_putc (struct ber*,unsigned long long) ; 
 int /*<<< orphan*/  ber_write (struct ber*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ber_dump_element(struct ber *ber, struct ber_element *root)
{
	unsigned long long l;
	int i;
	uint8_t u;

	ber_dump_header(ber, root);

	switch (root->be_encoding) {
	case BER_TYPE_BOOLEAN:
	case BER_TYPE_INTEGER:
	case BER_TYPE_ENUMERATED:
		l = (unsigned long long)root->be_numeric;
		for (i = root->be_len; i > 0; i--) {
			u = (l >> ((i - 1) * 8)) & 0xff;
			ber_putc(ber, u);
		}
		break;
	case BER_TYPE_BITSTRING:
		return -1;
	case BER_TYPE_OCTETSTRING:
	case BER_TYPE_OBJECT:
		ber_write(ber, root->be_val, root->be_len);
		break;
	case BER_TYPE_NULL:	/* no payload */
	case BER_TYPE_EOC:
		break;
	case BER_TYPE_SEQUENCE:
	case BER_TYPE_SET:
		if (root->be_sub && ber_dump_element(ber, root->be_sub) == -1)
			return -1;
		break;
	}

	if (root->be_next == NULL)
		return 0;
	return ber_dump_element(ber, root->be_next);
}