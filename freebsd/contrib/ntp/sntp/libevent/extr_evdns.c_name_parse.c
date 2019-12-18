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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GET8 (int) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 

__attribute__((used)) static int
name_parse(u8 *packet, int length, int *idx, char *name_out, int name_out_len) {
	int name_end = -1;
	int j = *idx;
	int ptr_count = 0;
#define GET32(x) do { if (j + 4 > length) goto err; memcpy(&t32_, packet + j, 4); j += 4; x = ntohl(t32_); } while (0)
#define GET16(x) do { if (j + 2 > length) goto err; memcpy(&t_, packet + j, 2); j += 2; x = ntohs(t_); } while (0)
#define GET8(x) do { if (j >= length) goto err; x = packet[j++]; } while (0)

	char *cp = name_out;
	const char *const end = name_out + name_out_len;

	/* Normally, names are a series of length prefixed strings terminated */
	/* with a length of 0 (the lengths are u8's < 63). */
	/* However, the length can start with a pair of 1 bits and that */
	/* means that the next 14 bits are a pointer within the current */
	/* packet. */

	for (;;) {
		u8 label_len;
		if (j >= length) return -1;
		GET8(label_len);
		if (!label_len) break;
		if (label_len & 0xc0) {
			u8 ptr_low;
			GET8(ptr_low);
			if (name_end < 0) name_end = j;
			j = (((int)label_len & 0x3f) << 8) + ptr_low;
			/* Make sure that the target offset is in-bounds. */
			if (j < 0 || j >= length) return -1;
			/* If we've jumped more times than there are characters in the
			 * message, we must have a loop. */
			if (++ptr_count > length) return -1;
			continue;
		}
		if (label_len > 63) return -1;
		if (cp != name_out) {
			if (cp + 1 >= end) return -1;
			*cp++ = '.';
		}
		if (cp + label_len >= end) return -1;
		memcpy(cp, packet + j, label_len);
		cp += label_len;
		j += label_len;
	}
	if (cp >= end) return -1;
	*cp = '\0';
	if (name_end < 0)
		*idx = j;
	else
		*idx = name_end;
	return 0;
 err:
	return -1;
}