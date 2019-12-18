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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PPB_BYTE 131 
#define  PPB_FORWARD_IDLE 130 
#define  PPB_NIBBLE 129 
#define  PPB_REVERSE_IDLE 128 
 int const PPB_REVERSE_TRANSFER ; 
 int /*<<< orphan*/  byte_1284_inbyte (int /*<<< orphan*/ ,char*) ; 
 int nFAULT ; 
 int /*<<< orphan*/  nibble_1284_inbyte (int /*<<< orphan*/ ,char*) ; 
 int ppb_1284_get_state (int /*<<< orphan*/ ) ; 
 int ppb_1284_negociate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_1284_set_state (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ppb_1284_terminate (int /*<<< orphan*/ ) ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
spp_1284_read(device_t bus, int mode, char *buffer, int max, int *read)
{
	int error = 0, len = 0;
	int terminate_after_transfer = 1;
	int state;

	*read = len = 0;

	state = ppb_1284_get_state(bus);

	switch (state) {
	case PPB_FORWARD_IDLE:
		if ((error = ppb_1284_negociate(bus, mode, 0)))
			return (error);
		break;

	case PPB_REVERSE_IDLE:
		terminate_after_transfer = 0;
		break;

	default:
		ppb_1284_terminate(bus);
		if ((error = ppb_1284_negociate(bus, mode, 0)))
			return (error);
		break;
	}

	while ((len < max) && !(ppb_rstr(bus) & (nFAULT))) {

		ppb_1284_set_state(bus, PPB_REVERSE_TRANSFER);

#ifdef DEBUG_1284
		printf("B");
#endif

		switch (mode) {
		case PPB_NIBBLE:
			/* read a byte, error means no more data */
			if (nibble_1284_inbyte(bus, buffer+len))
				goto end_while;
			break;
		case PPB_BYTE:
			if (byte_1284_inbyte(bus, buffer+len))
				goto end_while;
			break;
		default:
			error = EINVAL;
			goto end_while;
		}
		len ++;
	}
end_while:

	if (!error)
		ppb_1284_set_state(bus, PPB_REVERSE_IDLE);

	*read = len;

	if (terminate_after_transfer || error)
		ppb_1284_terminate(bus);

	return (error);
}