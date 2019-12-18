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
typedef  int uint64_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,long,char) ; 

__attribute__((used)) static char *
display_size(uint64_t size, u_int sectorsize)
{
	static char buf[80];
	char unit;

	size = size * sectorsize / 1024;
	unit = 'K';
	if (size >= 10485760000LL) {
		size /= 1073741824;
		unit = 'T';
	} else if (size >= 10240000) {
		size /= 1048576;
		unit = 'G';
	} else if (size >= 10000) {
		size /= 1024;
		unit = 'M';
	}
	snprintf(buf, sizeof(buf), "%4ld%cB", (long)size, unit);
	return (buf);
}