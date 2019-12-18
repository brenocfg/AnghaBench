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
struct TYPE_2__ {void* client_data; int /*<<< orphan*/ * callback; } ;
struct archive_read {TYPE_1__ passphrases; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  archive_passphrase_callback ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
archive_read_set_passphrase_callback(struct archive *_a, void *client_data,
    archive_passphrase_callback *cb)
{
	struct archive_read *a = (struct archive_read *)_a;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
		"archive_read_set_passphrase_callback");

	a->passphrases.callback = cb;
	a->passphrases.client_data = client_data;
	return (ARCHIVE_OK);
}