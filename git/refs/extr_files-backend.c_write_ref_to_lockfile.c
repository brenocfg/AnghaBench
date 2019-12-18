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
struct strbuf {int dummy; } ;
struct ref_lock {int /*<<< orphan*/  lk; int /*<<< orphan*/  ref_name; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; } ;
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ close_ref_gently (struct ref_lock*) ; 
 int get_lock_file_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_lock_file_path (int /*<<< orphan*/ *) ; 
 scalar_t__ is_branch (int /*<<< orphan*/ ) ; 
 char* oid_to_hex (struct object_id const*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,...) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  unlock_ref (struct ref_lock*) ; 
 scalar_t__ write_in_full (int,char*,int) ; 

__attribute__((used)) static int write_ref_to_lockfile(struct ref_lock *lock,
				 const struct object_id *oid, struct strbuf *err)
{
	static char term = '\n';
	struct object *o;
	int fd;

	o = parse_object(the_repository, oid);
	if (!o) {
		strbuf_addf(err,
			    "trying to write ref '%s' with nonexistent object %s",
			    lock->ref_name, oid_to_hex(oid));
		unlock_ref(lock);
		return -1;
	}
	if (o->type != OBJ_COMMIT && is_branch(lock->ref_name)) {
		strbuf_addf(err,
			    "trying to write non-commit object %s to branch '%s'",
			    oid_to_hex(oid), lock->ref_name);
		unlock_ref(lock);
		return -1;
	}
	fd = get_lock_file_fd(&lock->lk);
	if (write_in_full(fd, oid_to_hex(oid), the_hash_algo->hexsz) < 0 ||
	    write_in_full(fd, &term, 1) < 0 ||
	    close_ref_gently(lock) < 0) {
		strbuf_addf(err,
			    "couldn't write '%s'", get_lock_file_path(&lock->lk));
		unlock_ref(lock);
		return -1;
	}
	return 0;
}