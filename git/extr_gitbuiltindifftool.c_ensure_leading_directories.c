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
#define  SCLD_EXISTS 129 
#define  SCLD_OK 128 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char*) ; 
 int safe_create_leading_directories (char*) ; 

__attribute__((used)) static int ensure_leading_directories(char *path)
{
	switch (safe_create_leading_directories(path)) {
		case SCLD_OK:
		case SCLD_EXISTS:
			return 0;
		default:
			return error(_("could not create leading directories "
				       "of '%s'"), path);
	}
}