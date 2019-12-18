#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  maxhops_discovered; TYPE_1__* from_node; } ;
typedef  TYPE_2__ ibnd_fabric_t ;
struct TYPE_4__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int IBND_FABRIC_CACHE_BUFLEN ; 
 int /*<<< orphan*/  IBND_FABRIC_CACHE_MAGIC ; 
 int /*<<< orphan*/  IBND_FABRIC_CACHE_VERSION ; 
 scalar_t__ _marshall32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _marshall64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ibnd_write (int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int _cache_header_info(int fd, ibnd_fabric_t * fabric)
{
	uint8_t buf[IBND_FABRIC_CACHE_BUFLEN];
	size_t offset = 0;

	/* Store magic number, version, and other important info */
	/* For this caching lib, we always assume cached as little endian */

	offset += _marshall32(buf + offset, IBND_FABRIC_CACHE_MAGIC);
	offset += _marshall32(buf + offset, IBND_FABRIC_CACHE_VERSION);
	/* save space for node count */
	offset += _marshall32(buf + offset, 0);
	/* save space for port count */
	offset += _marshall32(buf + offset, 0);
	offset += _marshall64(buf + offset, fabric->from_node->guid);
	offset += _marshall32(buf + offset, fabric->maxhops_discovered);

	if (ibnd_write(fd, buf, offset) < 0)
		return -1;

	return 0;
}