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
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int index_bulk_checkin (struct object_id*,int,size_t,int,char const*,unsigned int) ; 

__attribute__((used)) static int index_stream(struct object_id *oid, int fd, size_t size,
			enum object_type type, const char *path,
			unsigned flags)
{
	return index_bulk_checkin(oid, fd, size, type, path, flags);
}