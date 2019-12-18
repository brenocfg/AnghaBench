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
struct cam_status_entry {int status_code; } ;
typedef  int cam_status ;

/* Variables and functions */

__attribute__((used)) static int
camstatusentrycomp(const void *key, const void *member)
{
	cam_status status;
	const struct cam_status_entry *table_entry;

	status = *(const cam_status *)key;
	table_entry = (const struct cam_status_entry *)member;

	return (status - table_entry->status_code);
}