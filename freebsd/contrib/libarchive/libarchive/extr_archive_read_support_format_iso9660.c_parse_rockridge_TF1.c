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
struct file_info {int birthtime_is_set; void* ctime; void* atime; void* mtime; void* birthtime; } ;

/* Variables and functions */
 void* isodate17 (unsigned char const*) ; 
 void* isodate7 (unsigned char const*) ; 

__attribute__((used)) static void
parse_rockridge_TF1(struct file_info *file, const unsigned char *data,
    int data_length)
{
	char flag;
	/*
	 * TF extension comprises:
	 *   one byte flag
	 *   create time (optional)
	 *   modify time (optional)
	 *   access time (optional)
	 *   attribute time (optional)
	 *  Time format and presence of fields
	 *  is controlled by flag bits.
	 */
	if (data_length < 1)
		return;
	flag = data[0];
	++data;
	--data_length;
	if (flag & 0x80) {
		/* Use 17-byte time format. */
		if ((flag & 1) && data_length >= 17) {
			/* Create time. */
			file->birthtime_is_set = 1;
			file->birthtime = isodate17(data);
			data += 17;
			data_length -= 17;
		}
		if ((flag & 2) && data_length >= 17) {
			/* Modify time. */
			file->mtime = isodate17(data);
			data += 17;
			data_length -= 17;
		}
		if ((flag & 4) && data_length >= 17) {
			/* Access time. */
			file->atime = isodate17(data);
			data += 17;
			data_length -= 17;
		}
		if ((flag & 8) && data_length >= 17) {
			/* Attribute change time. */
			file->ctime = isodate17(data);
		}
	} else {
		/* Use 7-byte time format. */
		if ((flag & 1) && data_length >= 7) {
			/* Create time. */
			file->birthtime_is_set = 1;
			file->birthtime = isodate7(data);
			data += 7;
			data_length -= 7;
		}
		if ((flag & 2) && data_length >= 7) {
			/* Modify time. */
			file->mtime = isodate7(data);
			data += 7;
			data_length -= 7;
		}
		if ((flag & 4) && data_length >= 7) {
			/* Access time. */
			file->atime = isodate7(data);
			data += 7;
			data_length -= 7;
		}
		if ((flag & 8) && data_length >= 7) {
			/* Attribute change time. */
			file->ctime = isodate7(data);
		}
	}
}