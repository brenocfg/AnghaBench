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
struct strbuf {int dummy; } ;
struct ref_store {int dummy; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_STORE_WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ log_ref_setup (struct files_ref_store*,char const*,int,int*,struct strbuf*) ; 

__attribute__((used)) static int files_create_reflog(struct ref_store *ref_store,
			       const char *refname, int force_create,
			       struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "create_reflog");
	int fd;

	if (log_ref_setup(refs, refname, force_create, &fd, err))
		return -1;

	if (fd >= 0)
		close(fd);

	return 0;
}