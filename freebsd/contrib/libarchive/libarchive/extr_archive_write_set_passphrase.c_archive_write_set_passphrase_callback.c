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
struct archive_write {void* passphrase_client_data; int /*<<< orphan*/ * passphrase_callback; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  archive_passphrase_callback ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
archive_write_set_passphrase_callback(struct archive *_a, void *client_data,
    archive_passphrase_callback *cb)
{
	struct archive_write *a = (struct archive_write *)_a;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC, ARCHIVE_STATE_NEW,
		"archive_write_set_passphrase_callback");

	a->passphrase_callback = cb;
	a->passphrase_client_data = client_data;
	return (ARCHIVE_OK);
}