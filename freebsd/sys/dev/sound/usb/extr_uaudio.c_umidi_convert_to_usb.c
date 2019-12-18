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
struct umidi_sub_chan {int* temp_0; int* temp_cmd; int* temp_1; int state; } ;

/* Variables and functions */
#define  UMIDI_ST_1PARAM 133 
#define  UMIDI_ST_2PARAM_1 132 
#define  UMIDI_ST_2PARAM_2 131 
#define  UMIDI_ST_SYSEX_0 130 
#define  UMIDI_ST_SYSEX_1 129 
#define  UMIDI_ST_SYSEX_2 128 
 void* UMIDI_ST_UNKNOWN ; 

__attribute__((used)) static uint8_t
umidi_convert_to_usb(struct umidi_sub_chan *sub, uint8_t cn, uint8_t b)
{
	uint8_t p0 = (cn << 4);

	if (b >= 0xf8) {
		sub->temp_0[0] = p0 | 0x0f;
		sub->temp_0[1] = b;
		sub->temp_0[2] = 0;
		sub->temp_0[3] = 0;
		sub->temp_cmd = sub->temp_0;
		return (1);

	} else if (b >= 0xf0) {
		switch (b) {
		case 0xf0:		/* system exclusive begin */
			sub->temp_1[1] = b;
			sub->state = UMIDI_ST_SYSEX_1;
			break;
		case 0xf1:		/* MIDI time code */
		case 0xf3:		/* song select */
			sub->temp_1[1] = b;
			sub->state = UMIDI_ST_1PARAM;
			break;
		case 0xf2:		/* song position pointer */
			sub->temp_1[1] = b;
			sub->state = UMIDI_ST_2PARAM_1;
			break;
		case 0xf4:		/* unknown */
		case 0xf5:		/* unknown */
			sub->state = UMIDI_ST_UNKNOWN;
			break;
		case 0xf6:		/* tune request */
			sub->temp_1[0] = p0 | 0x05;
			sub->temp_1[1] = 0xf6;
			sub->temp_1[2] = 0;
			sub->temp_1[3] = 0;
			sub->temp_cmd = sub->temp_1;
			sub->state = UMIDI_ST_UNKNOWN;
			return (1);

		case 0xf7:		/* system exclusive end */
			switch (sub->state) {
			case UMIDI_ST_SYSEX_0:
				sub->temp_1[0] = p0 | 0x05;
				sub->temp_1[1] = 0xf7;
				sub->temp_1[2] = 0;
				sub->temp_1[3] = 0;
				sub->temp_cmd = sub->temp_1;
				sub->state = UMIDI_ST_UNKNOWN;
				return (1);
			case UMIDI_ST_SYSEX_1:
				sub->temp_1[0] = p0 | 0x06;
				sub->temp_1[2] = 0xf7;
				sub->temp_1[3] = 0;
				sub->temp_cmd = sub->temp_1;
				sub->state = UMIDI_ST_UNKNOWN;
				return (1);
			case UMIDI_ST_SYSEX_2:
				sub->temp_1[0] = p0 | 0x07;
				sub->temp_1[3] = 0xf7;
				sub->temp_cmd = sub->temp_1;
				sub->state = UMIDI_ST_UNKNOWN;
				return (1);
			}
			sub->state = UMIDI_ST_UNKNOWN;
			break;
		}
	} else if (b >= 0x80) {
		sub->temp_1[1] = b;
		if ((b >= 0xc0) && (b <= 0xdf)) {
			sub->state = UMIDI_ST_1PARAM;
		} else {
			sub->state = UMIDI_ST_2PARAM_1;
		}
	} else {			/* b < 0x80 */
		switch (sub->state) {
		case UMIDI_ST_1PARAM:
			if (sub->temp_1[1] < 0xf0) {
				p0 |= sub->temp_1[1] >> 4;
			} else {
				p0 |= 0x02;
				sub->state = UMIDI_ST_UNKNOWN;
			}
			sub->temp_1[0] = p0;
			sub->temp_1[2] = b;
			sub->temp_1[3] = 0;
			sub->temp_cmd = sub->temp_1;
			return (1);
		case UMIDI_ST_2PARAM_1:
			sub->temp_1[2] = b;
			sub->state = UMIDI_ST_2PARAM_2;
			break;
		case UMIDI_ST_2PARAM_2:
			if (sub->temp_1[1] < 0xf0) {
				p0 |= sub->temp_1[1] >> 4;
				sub->state = UMIDI_ST_2PARAM_1;
			} else {
				p0 |= 0x03;
				sub->state = UMIDI_ST_UNKNOWN;
			}
			sub->temp_1[0] = p0;
			sub->temp_1[3] = b;
			sub->temp_cmd = sub->temp_1;
			return (1);
		case UMIDI_ST_SYSEX_0:
			sub->temp_1[1] = b;
			sub->state = UMIDI_ST_SYSEX_1;
			break;
		case UMIDI_ST_SYSEX_1:
			sub->temp_1[2] = b;
			sub->state = UMIDI_ST_SYSEX_2;
			break;
		case UMIDI_ST_SYSEX_2:
			sub->temp_1[0] = p0 | 0x04;
			sub->temp_1[3] = b;
			sub->temp_cmd = sub->temp_1;
			sub->state = UMIDI_ST_SYSEX_0;
			return (1);
		default:
			break;
		}
	}
	return (0);
}