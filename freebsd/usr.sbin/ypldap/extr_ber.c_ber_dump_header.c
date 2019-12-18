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
typedef  size_t u_char ;
struct ber_element {size_t be_type; size_t be_class; scalar_t__ be_encoding; unsigned long be_len; } ;
struct ber {int dummy; } ;

/* Variables and functions */
 size_t BER_CLASS_SHIFT ; 
 size_t BER_TAG_MASK ; 
 unsigned long BER_TAG_MORE ; 
 size_t BER_TYPE_CONSTRUCTED ; 
 scalar_t__ BER_TYPE_SEQUENCE ; 
 scalar_t__ BER_TYPE_SET ; 
 size_t BER_TYPE_SINGLE_MAX ; 
 int /*<<< orphan*/  ber_putc (struct ber*,size_t) ; 

__attribute__((used)) static void
ber_dump_header(struct ber *ber, struct ber_element *root)
{
	u_char	id = 0, t, buf[8];
	unsigned long type;
	size_t size;

	/* class universal, type encoding depending on type value */
	/* length encoding */
	if (root->be_type <= BER_TYPE_SINGLE_MAX) {
		id = root->be_type | (root->be_class << BER_CLASS_SHIFT);
		if (root->be_encoding == BER_TYPE_SEQUENCE ||
		    root->be_encoding == BER_TYPE_SET)
			id |= BER_TYPE_CONSTRUCTED;

		ber_putc(ber, id);
	} else {
		id = BER_TAG_MASK | (root->be_class << BER_CLASS_SHIFT);
		if (root->be_encoding == BER_TYPE_SEQUENCE ||
		    root->be_encoding == BER_TYPE_SET)
			id |= BER_TYPE_CONSTRUCTED;

		ber_putc(ber, id);

		for (t = 0, type = root->be_type; type > 0; type >>= 7)
			buf[t++] = type & ~BER_TAG_MORE;

		while (t-- > 0) {
			if (t > 0)
				buf[t] |= BER_TAG_MORE;
			ber_putc(ber, buf[t]);
		}
	}

	if (root->be_len < BER_TAG_MORE) {
		/* short form */
		ber_putc(ber, root->be_len);
	} else {
		for (t = 0, size = root->be_len; size > 0; size >>= 8)
			buf[t++] = size & 0xff;

		ber_putc(ber, t | BER_TAG_MORE);

		while (t > 0)
			ber_putc(ber, buf[--t]);
	}
}