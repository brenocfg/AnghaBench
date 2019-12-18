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
 char* Base64 ; 
 char Pad64 ; 
 int /*<<< orphan*/  assert (int) ; 

int
ldns_b64_ntop(uint8_t const *src, size_t srclength, char *target, size_t targsize) {
	size_t datalength = 0;
	uint8_t input[3];
	uint8_t output[4];
	size_t i;
	
	if (srclength == 0) {
		if (targsize > 0) {
			target[0] = '\0';
			return 0;
		} else {
			return -1;
		}
	}

	while (2 < srclength) {
		input[0] = *src++;
		input[1] = *src++;
		input[2] = *src++;
		srclength -= 3;

		output[0] = input[0] >> 2;
		output[1] = ((input[0] & 0x03) << 4) + (input[1] >> 4);
		output[2] = ((input[1] & 0x0f) << 2) + (input[2] >> 6);
		output[3] = input[2] & 0x3f;
		assert(output[0] < 64);
		assert(output[1] < 64);
		assert(output[2] < 64);
		assert(output[3] < 64);

		if (datalength + 4 > targsize) {
			return (-1);
		}
		target[datalength++] = Base64[output[0]];
		target[datalength++] = Base64[output[1]];
		target[datalength++] = Base64[output[2]];
		target[datalength++] = Base64[output[3]];
	}
    
	/* Now we worry about padding. */
	if (0 != srclength) {
		/* Get what's left. */
		input[0] = input[1] = input[2] = (uint8_t) '\0';
		for (i = 0; i < srclength; i++)
			input[i] = *src++;
	
		output[0] = input[0] >> 2;
		output[1] = ((input[0] & 0x03) << 4) + (input[1] >> 4);
		output[2] = ((input[1] & 0x0f) << 2) + (input[2] >> 6);
		assert(output[0] < 64);
		assert(output[1] < 64);
		assert(output[2] < 64);

		if (datalength + 4 > targsize) {
			return (-2);
		}
		target[datalength++] = Base64[output[0]];
		target[datalength++] = Base64[output[1]];
		if (srclength == 1) {
			target[datalength++] = Pad64;
		} else {
			target[datalength++] = Base64[output[2]];
		}
		target[datalength++] = Pad64;
	}
	if (datalength >= targsize) {
		return (-3);
	}
	target[datalength] = '\0';	/* Returned value doesn't count \0. */
	return (int) (datalength);
}