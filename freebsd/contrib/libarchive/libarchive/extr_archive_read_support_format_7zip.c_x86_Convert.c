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
typedef  int uint32_t ;
struct _7zip {size_t bcj_prevPosT; int bcj_prevMask; int bcj_ip; } ;

/* Variables and functions */
 scalar_t__ Test86MSByte (int) ; 

__attribute__((used)) static size_t
x86_Convert(struct _7zip *zip, uint8_t *data, size_t size)
{
	static const uint8_t kMaskToAllowedStatus[8] = {1, 1, 1, 0, 1, 0, 0, 0};
	static const uint8_t kMaskToBitNumber[8] = {0, 1, 2, 2, 3, 3, 3, 3};
	size_t bufferPos, prevPosT;
	uint32_t ip, prevMask;

	if (size < 5)
		return 0;

	bufferPos = 0;
	prevPosT = zip->bcj_prevPosT;
	prevMask = zip->bcj_prevMask;
	ip = zip->bcj_ip;

	for (;;) {
		uint8_t *p = data + bufferPos;
		uint8_t *limit = data + size - 4;

		for (; p < limit; p++)
			if ((*p & 0xFE) == 0xE8)
				break;
		bufferPos = (size_t)(p - data);
		if (p >= limit)
			break;
		prevPosT = bufferPos - prevPosT;
		if (prevPosT > 3)
			prevMask = 0;
		else {
			prevMask = (prevMask << ((int)prevPosT - 1)) & 0x7;
			if (prevMask != 0) {
				unsigned char b =
					p[4 - kMaskToBitNumber[prevMask]];
				if (!kMaskToAllowedStatus[prevMask] ||
				    Test86MSByte(b)) {
					prevPosT = bufferPos;
					prevMask = ((prevMask << 1) & 0x7) | 1;
					bufferPos++;
					continue;
				}
			}
		}
		prevPosT = bufferPos;

		if (Test86MSByte(p[4])) {
			uint32_t src = ((uint32_t)p[4] << 24) |
				((uint32_t)p[3] << 16) | ((uint32_t)p[2] << 8) |
				((uint32_t)p[1]);
			uint32_t dest;
			for (;;) {
				uint8_t b;
				int b_index;

				dest = src - (ip + (uint32_t)bufferPos);
				if (prevMask == 0)
					break;
				b_index = kMaskToBitNumber[prevMask] * 8;
				b = (uint8_t)(dest >> (24 - b_index));
				if (!Test86MSByte(b))
					break;
				src = dest ^ ((1 << (32 - b_index)) - 1);
			}
			p[4] = (uint8_t)(~(((dest >> 24) & 1) - 1));
			p[3] = (uint8_t)(dest >> 16);
			p[2] = (uint8_t)(dest >> 8);
			p[1] = (uint8_t)dest;
			bufferPos += 5;
		} else {
			prevMask = ((prevMask << 1) & 0x7) | 1;
			bufferPos++;
		}
	}
	zip->bcj_prevPosT = prevPosT;
	zip->bcj_prevMask = prevMask;
	zip->bcj_ip += (uint32_t)bufferPos;
	return (bufferPos);
}