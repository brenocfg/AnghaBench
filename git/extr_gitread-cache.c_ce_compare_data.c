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
struct stat {int dummy; } ;
struct object_id {int dummy; } ;
struct index_state {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_BLOB ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int git_open_cloexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_fd (struct index_state*,struct object_id*,int,struct stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oideq (struct object_id*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ce_compare_data(struct index_state *istate,
			   const struct cache_entry *ce,
			   struct stat *st)
{
	int match = -1;
	int fd = git_open_cloexec(ce->name, O_RDONLY);

	if (fd >= 0) {
		struct object_id oid;
		if (!index_fd(istate, &oid, fd, st, OBJ_BLOB, ce->name, 0))
			match = !oideq(&oid, &ce->oid);
		/* index_fd() closed the file descriptor already */
	}
	return match;
}