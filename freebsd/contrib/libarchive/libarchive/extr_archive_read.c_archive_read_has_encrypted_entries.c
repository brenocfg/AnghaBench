#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read {TYPE_1__* format; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {int (* has_encrypted_entries ) (struct archive_read*) ;} ;

/* Variables and functions */
 int ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA ; 
 int ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA ; 
 int ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int archive_read_format_capabilities (struct archive*) ; 
 int stub1 (struct archive_read*) ; 

int
archive_read_has_encrypted_entries(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	int format_supports_encryption = archive_read_format_capabilities(_a)
			& (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA | ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);

	if (!_a || !format_supports_encryption) {
		/* Format in general doesn't support encryption */
		return ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED;
	}

	/* A reader potentially has read enough data now. */
	if (a->format && a->format->has_encrypted_entries) {
		return (a->format->has_encrypted_entries)(a);
	}

	/* For any other reason we cannot say how many entries are there. */
	return ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW;
}