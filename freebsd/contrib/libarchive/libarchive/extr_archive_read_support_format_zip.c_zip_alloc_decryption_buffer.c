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
struct zip {size_t decrypted_buffer_size; int /*<<< orphan*/ * decrypted_buffer; int /*<<< orphan*/ * decrypted_ptr; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

__attribute__((used)) static int
zip_alloc_decryption_buffer(struct archive_read *a)
{
	struct zip *zip = (struct zip *)(a->format->data);
	size_t bs = 256 * 1024;

	if (zip->decrypted_buffer == NULL) {
		zip->decrypted_buffer_size = bs;
		zip->decrypted_buffer = malloc(bs);
		if (zip->decrypted_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for ZIP decryption");
			return (ARCHIVE_FATAL);
		}
	}
	zip->decrypted_ptr = zip->decrypted_buffer;
	return (ARCHIVE_OK);
}