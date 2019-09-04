#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int* w; int /*<<< orphan*/  const* b; } ;
struct TYPE_6__ {int bufOffset; int byteCount; TYPE_1__ state; } ;
typedef  TYPE_2__ sha1nfo ;

/* Variables and functions */
 int /*<<< orphan*/  sha1_add (TYPE_2__*,int) ; 

const uint8_t *sha1_final(sha1nfo *s)
{
	int i;
	sha1_add(s, 0x80);
	while (s->bufOffset != 56) sha1_add(s, 0);
	sha1_add(s, 0);
	sha1_add(s, 0);
	sha1_add(s, 0);
	sha1_add(s, s->byteCount >> 29);
	sha1_add(s, s->byteCount >> 21);
	sha1_add(s, s->byteCount >> 13);
	sha1_add(s, s->byteCount >> 5);
	sha1_add(s, s->byteCount << 3);
	for (i = 0; i < 5; ++i) {
		uint32_t a = s->state.w[i];
		s->state.w[i] = a<<24 | (a<<8&0x00ff0000) | (a>>8&0x0000ff00) | a>>24;
	}
	return s->state.b;
}