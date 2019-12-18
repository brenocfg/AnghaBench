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
struct ber_element {scalar_t__ be_encoding; size_t be_len; unsigned long be_type; struct ber_element* be_next; struct ber_element* be_sub; } ;

/* Variables and functions */
 size_t BER_TAG_MORE ; 
 unsigned long BER_TYPE_EOC ; 
 scalar_t__ BER_TYPE_SEQUENCE ; 
 scalar_t__ BER_TYPE_SET ; 
 unsigned long BER_TYPE_SINGLE_MAX ; 

size_t
ber_calc_len(struct ber_element *root)
{
	unsigned long t;
	size_t s;
	size_t size = 2;	/* minimum 1 byte head and 1 byte size */

	/* calculate the real length of a sequence or set */
	if (root->be_sub && (root->be_encoding == BER_TYPE_SEQUENCE ||
	    root->be_encoding == BER_TYPE_SET))
		root->be_len = ber_calc_len(root->be_sub);

	/* fix header length for extended types */
	if (root->be_type > BER_TYPE_SINGLE_MAX)
		for (t = root->be_type; t > 0; t >>= 7)
			size++;
	if (root->be_len >= BER_TAG_MORE)
		for (s = root->be_len; s > 0; s >>= 8)
			size++;

	/* calculate the length of the following elements */
	if (root->be_next)
		size += ber_calc_len(root->be_next);

	/* This is an empty element, do not use a minimal size */
	if (root->be_type == BER_TYPE_EOC && root->be_len == 0)
		return (0);

	return (root->be_len + size);
}