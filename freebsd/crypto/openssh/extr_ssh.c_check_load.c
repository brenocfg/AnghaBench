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
 int /*<<< orphan*/  ENOENT ; 
#define  SSH_ERR_ALLOC_FAIL 130 
#define  SSH_ERR_INTERNAL_ERROR 129 
#define  SSH_ERR_SYSTEM_ERROR 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_err (int) ; 

__attribute__((used)) static void
check_load(int r, const char *path, const char *message)
{
	switch (r) {
	case 0:
		break;
	case SSH_ERR_INTERNAL_ERROR:
	case SSH_ERR_ALLOC_FAIL:
		fatal("load %s \"%s\": %s", message, path, ssh_err(r));
	case SSH_ERR_SYSTEM_ERROR:
		/* Ignore missing files */
		if (errno == ENOENT)
			break;
		/* FALLTHROUGH */
	default:
		error("load %s \"%s\": %s", message, path, ssh_err(r));
		break;
	}
}