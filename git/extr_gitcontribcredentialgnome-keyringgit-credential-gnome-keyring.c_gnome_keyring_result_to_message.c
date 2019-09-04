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
typedef  int GnomeKeyringResult ;

/* Variables and functions */
#define  GNOME_KEYRING_RESULT_ALREADY_EXISTS 136 
#define  GNOME_KEYRING_RESULT_ALREADY_UNLOCKED 135 
#define  GNOME_KEYRING_RESULT_BAD_ARGUMENTS 134 
#define  GNOME_KEYRING_RESULT_CANCELLED 133 
#define  GNOME_KEYRING_RESULT_DENIED 132 
#define  GNOME_KEYRING_RESULT_IO_ERROR 131 
#define  GNOME_KEYRING_RESULT_NO_KEYRING_DAEMON 130 
#define  GNOME_KEYRING_RESULT_NO_SUCH_KEYRING 129 
#define  GNOME_KEYRING_RESULT_OK 128 

__attribute__((used)) static const char *gnome_keyring_result_to_message(GnomeKeyringResult result)
{
	switch (result) {
	case GNOME_KEYRING_RESULT_OK:
		return "OK";
	case GNOME_KEYRING_RESULT_DENIED:
		return "Denied";
	case GNOME_KEYRING_RESULT_NO_KEYRING_DAEMON:
		return "No Keyring Daemon";
	case GNOME_KEYRING_RESULT_ALREADY_UNLOCKED:
		return "Already UnLocked";
	case GNOME_KEYRING_RESULT_NO_SUCH_KEYRING:
		return "No Such Keyring";
	case GNOME_KEYRING_RESULT_BAD_ARGUMENTS:
		return "Bad Arguments";
	case GNOME_KEYRING_RESULT_IO_ERROR:
		return "IO Error";
	case GNOME_KEYRING_RESULT_CANCELLED:
		return "Cancelled";
	case GNOME_KEYRING_RESULT_ALREADY_EXISTS:
		return "Already Exists";
	default:
		return "Unknown Error";
	}
}