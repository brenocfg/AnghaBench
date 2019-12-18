#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; } ;
struct file_info {int symlink_continues; TYPE_1__ symlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strcat (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_strncat (TYPE_1__*,char const*,unsigned char) ; 

__attribute__((used)) static void
parse_rockridge_SL1(struct file_info *file, const unsigned char *data,
    int data_length)
{
	const char *separator = "";

	if (!file->symlink_continues || file->symlink.length < 1)
		archive_string_empty(&file->symlink);
	file->symlink_continues = 0;

	/*
	 * Defined flag values:
	 *  0: This is the last SL record for this symbolic link
	 *  1: this symbolic link field continues in next SL entry
	 *  All other values are reserved.
	 */
	if (data_length < 1)
		return;
	switch(*data) {
	case 0:
		break;
	case 1:
		file->symlink_continues = 1;
		break;
	default:
		return;
	}
	++data;  /* Skip flag byte. */
	--data_length;

	/*
	 * SL extension body stores "components".
	 * Basically, this is a complicated way of storing
	 * a POSIX path.  It also interferes with using
	 * symlinks for storing non-path data. <sigh>
	 *
	 * Each component is 2 bytes (flag and length)
	 * possibly followed by name data.
	 */
	while (data_length >= 2) {
		unsigned char flag = *data++;
		unsigned char nlen = *data++;
		data_length -= 2;

		archive_strcat(&file->symlink, separator);
		separator = "/";

		switch(flag) {
		case 0: /* Usual case, this is text. */
			if (data_length < nlen)
				return;
			archive_strncat(&file->symlink,
			    (const char *)data, nlen);
			break;
		case 0x01: /* Text continues in next component. */
			if (data_length < nlen)
				return;
			archive_strncat(&file->symlink,
			    (const char *)data, nlen);
			separator = "";
			break;
		case 0x02: /* Current dir. */
			archive_strcat(&file->symlink, ".");
			break;
		case 0x04: /* Parent dir. */
			archive_strcat(&file->symlink, "..");
			break;
		case 0x08: /* Root of filesystem. */
			archive_strcat(&file->symlink, "/");
			separator = "";
			break;
		case 0x10: /* Undefined (historically "volume root" */
			archive_string_empty(&file->symlink);
			archive_strcat(&file->symlink, "ROOT");
			break;
		case 0x20: /* Undefined (historically "hostname") */
			archive_strcat(&file->symlink, "hostname");
			break;
		default:
			/* TODO: issue a warning ? */
			return;
		}
		data += nlen;
		data_length -= nlen;
	}
}