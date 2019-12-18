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
struct stat {int /*<<< orphan*/  st_dev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int,char const*,char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static dev_t get_device_or_die(const char *path, const char *prefix, int prefix_len)
{
	struct stat buf;
	if (stat(path, &buf)) {
		die_errno(_("failed to stat '%*s%s%s'"),
				prefix_len,
				prefix ? prefix : "",
				prefix ? "/" : "", path);
	}
	return buf.st_dev;
}