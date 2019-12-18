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
struct cache_header {int /*<<< orphan*/  hdr_version; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct cache_header*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int read (int /*<<< orphan*/ ,struct cache_header*,int) ; 

int cmd__index_version(int argc, const char **argv)
{
	struct cache_header hdr;
	int version;

	memset(&hdr,0,sizeof(hdr));
	if (read(0, &hdr, sizeof(hdr)) != sizeof(hdr))
		return 0;
	version = ntohl(hdr.hdr_version);
	printf("%d\n", version);
	return 0;
}