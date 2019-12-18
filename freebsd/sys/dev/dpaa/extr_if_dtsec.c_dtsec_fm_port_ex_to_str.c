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
typedef  int e_FmPortExceptions ;

/* Variables and functions */
#define  e_FM_PORT_EXCEPTION_IM_BUSY 128 

__attribute__((used)) static const char *
dtsec_fm_port_ex_to_str(e_FmPortExceptions exception)
{

	switch (exception) {
	case e_FM_PORT_EXCEPTION_IM_BUSY:
		return ("IM: RX busy");
	default:
		return ("<Unknown Exception>");
	}
}