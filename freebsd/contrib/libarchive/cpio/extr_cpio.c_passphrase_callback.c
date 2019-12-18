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
struct cpio {int /*<<< orphan*/ * ppbuff; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPBUFF_SIZE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 char const* lafe_readpassphrase (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
passphrase_callback(struct archive *a, void *_client_data)
{
	struct cpio *cpio = (struct cpio *)_client_data;
	(void)a; /* UNUSED */

	if (cpio->ppbuff == NULL) {
		cpio->ppbuff = malloc(PPBUFF_SIZE);
		if (cpio->ppbuff == NULL)
			lafe_errc(1, errno, "Out of memory");
	}
	return lafe_readpassphrase("Enter passphrase:",
		cpio->ppbuff, PPBUFF_SIZE);
}