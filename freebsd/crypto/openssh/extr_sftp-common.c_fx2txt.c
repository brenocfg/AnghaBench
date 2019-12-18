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
#define  SSH2_FX_BAD_MESSAGE 136 
#define  SSH2_FX_CONNECTION_LOST 135 
#define  SSH2_FX_EOF 134 
#define  SSH2_FX_FAILURE 133 
#define  SSH2_FX_NO_CONNECTION 132 
#define  SSH2_FX_NO_SUCH_FILE 131 
#define  SSH2_FX_OK 130 
#define  SSH2_FX_OP_UNSUPPORTED 129 
#define  SSH2_FX_PERMISSION_DENIED 128 

const char *
fx2txt(int status)
{
	switch (status) {
	case SSH2_FX_OK:
		return("No error");
	case SSH2_FX_EOF:
		return("End of file");
	case SSH2_FX_NO_SUCH_FILE:
		return("No such file or directory");
	case SSH2_FX_PERMISSION_DENIED:
		return("Permission denied");
	case SSH2_FX_FAILURE:
		return("Failure");
	case SSH2_FX_BAD_MESSAGE:
		return("Bad message");
	case SSH2_FX_NO_CONNECTION:
		return("No connection");
	case SSH2_FX_CONNECTION_LOST:
		return("Connection lost");
	case SSH2_FX_OP_UNSUPPORTED:
		return("Operation unsupported");
	default:
		return("Unknown status");
	}
	/* NOTREACHED */
}