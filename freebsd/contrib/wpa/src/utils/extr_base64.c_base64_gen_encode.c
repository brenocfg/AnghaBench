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

/* Variables and functions */
 int SIZE_MAX ; 
 unsigned char* os_malloc (size_t) ; 

__attribute__((used)) static unsigned char * base64_gen_encode(const unsigned char *src, size_t len,
					 size_t *out_len,
					 const unsigned char *table,
					 int add_pad)
{
	unsigned char *out, *pos;
	const unsigned char *end, *in;
	size_t olen;
	int line_len;

	if (len >= SIZE_MAX / 4)
		return NULL;
	olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
	if (add_pad)
		olen += olen / 72; /* line feeds */
	olen++; /* nul termination */
	if (olen < len)
		return NULL; /* integer overflow */
	out = os_malloc(olen);
	if (out == NULL)
		return NULL;

	end = src + len;
	in = src;
	pos = out;
	line_len = 0;
	while (end - in >= 3) {
		*pos++ = table[(in[0] >> 2) & 0x3f];
		*pos++ = table[(((in[0] & 0x03) << 4) | (in[1] >> 4)) & 0x3f];
		*pos++ = table[(((in[1] & 0x0f) << 2) | (in[2] >> 6)) & 0x3f];
		*pos++ = table[in[2] & 0x3f];
		in += 3;
		line_len += 4;
		if (add_pad && line_len >= 72) {
			*pos++ = '\n';
			line_len = 0;
		}
	}

	if (end - in) {
		*pos++ = table[(in[0] >> 2) & 0x3f];
		if (end - in == 1) {
			*pos++ = table[((in[0] & 0x03) << 4) & 0x3f];
			if (add_pad)
				*pos++ = '=';
		} else {
			*pos++ = table[(((in[0] & 0x03) << 4) |
					(in[1] >> 4)) & 0x3f];
			*pos++ = table[((in[1] & 0x0f) << 2) & 0x3f];
		}
		if (add_pad)
			*pos++ = '=';
		line_len += 4;
	}

	if (add_pad && line_len)
		*pos++ = '\n';

	*pos = '\0';
	if (out_len)
		*out_len = pos - out;
	return out;
}