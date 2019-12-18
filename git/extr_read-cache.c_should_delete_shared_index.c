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
struct stat {unsigned long st_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 unsigned long get_shared_index_expire_date () ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int should_delete_shared_index(const char *shared_index_path)
{
	struct stat st;
	unsigned long expiration;

	/* Check timestamp */
	expiration = get_shared_index_expire_date();
	if (!expiration)
		return 0;
	if (stat(shared_index_path, &st))
		return error_errno(_("could not stat '%s'"), shared_index_path);
	if (st.st_mtime > expiration)
		return 0;

	return 1;
}