#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 unsigned int HASH_WRITE_OBJECT ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ hash_literally (struct object_id*,int,char const*,unsigned int) ; 
 scalar_t__ index_fd (int /*<<< orphan*/ ,struct object_id*,int,struct stat*,int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  maybe_flush_or_die (int /*<<< orphan*/ ,char*) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_1__* the_repository ; 
 int /*<<< orphan*/  type_from_string (char const*) ; 

__attribute__((used)) static void hash_fd(int fd, const char *type, const char *path, unsigned flags,
		    int literally)
{
	struct stat st;
	struct object_id oid;

	if (fstat(fd, &st) < 0 ||
	    (literally
	     ? hash_literally(&oid, fd, type, flags)
	     : index_fd(the_repository->index, &oid, fd, &st,
			type_from_string(type), path, flags)))
		die((flags & HASH_WRITE_OBJECT)
		    ? "Unable to add %s to database"
		    : "Unable to hash %s", path);
	printf("%s\n", oid_to_hex(&oid));
	maybe_flush_or_die(stdout, "hash to stdout");
}