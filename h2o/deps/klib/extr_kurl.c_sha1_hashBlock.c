#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int* w; } ;
struct TYPE_5__ {int* w; } ;
struct TYPE_7__ {TYPE_2__ state; TYPE_1__ buf; } ;
typedef  TYPE_3__ sha1nfo ;

/* Variables and functions */
 int rol32 (int,int) ; 

__attribute__((used)) static void sha1_hashBlock(sha1nfo *s)
{
	uint32_t i, t, a = s->state.w[0], b = s->state.w[1], c = s->state.w[2], d = s->state.w[3], e = s->state.w[4];
	for (i = 0; i < 80; i++) {
		if (i >= 16) {
			t = s->buf.w[(i+13)&15] ^ s->buf.w[(i+8)&15] ^ s->buf.w[(i+2)&15] ^ s->buf.w[i&15];
			s->buf.w[i&15] = rol32(t, 1);
		}
		if (i < 20)      t = 0x5a827999 + (d ^ (b & (c ^ d)));
		else if (i < 40) t = 0x6ed9eba1 + (b ^ c ^ d);
		else if (i < 60) t = 0x8f1bbcdc + ((b & c) | (d & (b | c)));
		else             t = 0xca62c1d6 + (b ^ c ^ d);
		t += rol32(a, 5) + e + s->buf.w[i&15];
		e = d; d = c; c = rol32(b, 30); b = a; a = t;
	}
	s->state.w[0] += a; s->state.w[1] += b; s->state.w[2] += c; s->state.w[3] += d; s->state.w[4] += e;
}