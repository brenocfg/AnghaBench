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
typedef  int uint8_t ;

/* Variables and functions */
 size_t sldns_b64_ntop_calculate_size (size_t) ; 

int sldns_b64_ntop(uint8_t const *src, size_t srclength,
	char *target, size_t targsize)
{
	const char* b64 =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const char pad64 = '=';
	size_t i = 0, o = 0;
	if(targsize < sldns_b64_ntop_calculate_size(srclength))
		return -1;
	/* whole chunks: xxxxxxyy yyyyzzzz zzwwwwww */
	while(i+3 <= srclength) {
		if(o+4 > targsize) return -1;
		target[o] = b64[src[i] >> 2];
		target[o+1] = b64[ ((src[i]&0x03)<<4) | (src[i+1]>>4) ];
		target[o+2] = b64[ ((src[i+1]&0x0f)<<2) | (src[i+2]>>6) ];
		target[o+3] = b64[ (src[i+2]&0x3f) ];
		i += 3;
		o += 4;
	}
	/* remainder */
	switch(srclength - i) {
	case 2:
		/* two at end, converted into A B C = */
		target[o] = b64[src[i] >> 2];
		target[o+1] = b64[ ((src[i]&0x03)<<4) | (src[i+1]>>4) ];
		target[o+2] = b64[ ((src[i+1]&0x0f)<<2) ];
		target[o+3] = pad64;
		/* i += 2; */
		o += 4;
		break;
	case 1:
		/* one at end, converted into A B = = */
		target[o] = b64[src[i] >> 2];
		target[o+1] = b64[ ((src[i]&0x03)<<4) ];
		target[o+2] = pad64;
		target[o+3] = pad64;
		/* i += 1; */
		o += 4;
		break;
	case 0:
	default:
		/* nothing */
		break;
	}
	/* assert: i == srclength */
	if(o+1 > targsize) return -1;
	target[o] = 0;
	return (int)o;
}