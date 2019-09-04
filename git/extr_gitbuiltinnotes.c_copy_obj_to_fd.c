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
 int /*<<< orphan*/  free (char*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  write_or_die (int,char*,unsigned long) ; 

__attribute__((used)) static void copy_obj_to_fd(int fd, const struct object_id *oid)
{
	unsigned long size;
	enum object_type type;
	char *buf = read_object_file(oid, &type, &size);
	if (buf) {
		if (size)
			write_or_die(fd, buf, size);
		free(buf);
	}
}