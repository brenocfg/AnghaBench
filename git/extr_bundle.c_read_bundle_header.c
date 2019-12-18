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
struct bundle_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int parse_bundle_header (int,struct bundle_header*,char const*) ; 

int read_bundle_header(const char *path, struct bundle_header *header)
{
	int fd = open(path, O_RDONLY);

	if (fd < 0)
		return error(_("could not open '%s'"), path);
	return parse_bundle_header(fd, header, path);
}