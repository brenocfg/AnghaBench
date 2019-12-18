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
struct index_state {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 size_t SMALL_FILE_SIZE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int index_mem (struct index_state*,struct object_id*,void*,size_t,int,char const*,unsigned int) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 size_t read_in_full (int,char*,size_t) ; 
 char* xmalloc (size_t) ; 
 void* xmmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int index_core(struct index_state *istate,
		      struct object_id *oid, int fd, size_t size,
		      enum object_type type, const char *path,
		      unsigned flags)
{
	int ret;

	if (!size) {
		ret = index_mem(istate, oid, "", size, type, path, flags);
	} else if (size <= SMALL_FILE_SIZE) {
		char *buf = xmalloc(size);
		ssize_t read_result = read_in_full(fd, buf, size);
		if (read_result < 0)
			ret = error_errno(_("read error while indexing %s"),
					  path ? path : "<unknown>");
		else if (read_result != size)
			ret = error(_("short read while indexing %s"),
				    path ? path : "<unknown>");
		else
			ret = index_mem(istate, oid, buf, size, type, path, flags);
		free(buf);
	} else {
		void *buf = xmmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
		ret = index_mem(istate, oid, buf, size, type, path, flags);
		munmap(buf, size);
	}
	return ret;
}