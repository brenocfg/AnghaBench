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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ be32toh (scalar_t__) ; 
 void* dbm_base ; 
 scalar_t__ max_offset ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__,...) ; 

void *
dbm_get(int32_t offset)
{
	offset = be32toh(offset);
	if (offset < 0) {
		warnx("dbm_get: Database corrupt: offset %d", offset);
		return NULL;
	}
	if (offset >= max_offset) {
		warnx("dbm_get: Database corrupt: offset %d > %d",
		    offset, max_offset);
		return NULL;
	}
	return dbm_base + offset;
}