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
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  memset (struct bundle_header*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int parse_bundle_header (int,struct bundle_header*,char const*) ; 

int is_bundle(const char *path, int quiet)
{
	struct bundle_header header;
	int fd = open(path, O_RDONLY);

	if (fd < 0)
		return 0;
	memset(&header, 0, sizeof(header));
	fd = parse_bundle_header(fd, &header, quiet ? NULL : path);
	if (fd >= 0)
		close(fd);
	return (fd >= 0);
}