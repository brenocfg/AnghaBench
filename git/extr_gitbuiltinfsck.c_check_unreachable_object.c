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
struct object {int flags; scalar_t__ type; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HAS_OBJ ; 
 scalar_t__ OBJ_BLOB ; 
 scalar_t__ OBJ_COMMIT ; 
 int USED ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* describe_object (struct object*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* git_pathdup (char*,char*,char*) ; 
 int /*<<< orphan*/  printable_type (struct object*) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ safe_create_leading_directories_const (char*) ; 
 scalar_t__ show_dangling ; 
 scalar_t__ show_unreachable ; 
 scalar_t__ stream_blob_to_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ write_lost_and_found ; 
 int /*<<< orphan*/ * xfopen (char*,char*) ; 

__attribute__((used)) static void check_unreachable_object(struct object *obj)
{
	/*
	 * Missing unreachable object? Ignore it. It's not like
	 * we miss it (since it can't be reached), nor do we want
	 * to complain about it being unreachable (since it does
	 * not exist).
	 */
	if (!(obj->flags & HAS_OBJ))
		return;

	/*
	 * Unreachable object that exists? Show it if asked to,
	 * since this is something that is prunable.
	 */
	if (show_unreachable) {
		printf_ln(_("unreachable %s %s"), printable_type(obj),
			  describe_object(obj));
		return;
	}

	/*
	 * "!USED" means that nothing at all points to it, including
	 * other unreachable objects. In other words, it's the "tip"
	 * of some set of unreachable objects, usually a commit that
	 * got dropped.
	 *
	 * Such starting points are more interesting than some random
	 * set of unreachable objects, so we show them even if the user
	 * hasn't asked for _all_ unreachable objects. If you have
	 * deleted a branch by mistake, this is a prime candidate to
	 * start looking at, for example.
	 */
	if (!(obj->flags & USED)) {
		if (show_dangling)
			printf_ln(_("dangling %s %s"), printable_type(obj),
				  describe_object(obj));
		if (write_lost_and_found) {
			char *filename = git_pathdup("lost-found/%s/%s",
				obj->type == OBJ_COMMIT ? "commit" : "other",
				describe_object(obj));
			FILE *f;

			if (safe_create_leading_directories_const(filename)) {
				error(_("could not create lost-found"));
				free(filename);
				return;
			}
			f = xfopen(filename, "w");
			if (obj->type == OBJ_BLOB) {
				if (stream_blob_to_fd(fileno(f), &obj->oid, NULL, 1))
					die_errno(_("could not write '%s'"), filename);
			} else
				fprintf(f, "%s\n", describe_object(obj));
			if (fclose(f))
				die_errno(_("could not finish '%s'"),
					  filename);
			free(filename);
		}
		return;
	}

	/*
	 * Otherwise? It's there, it's unreachable, and some other unreachable
	 * object points to it. Ignore it - it's not interesting, and we showed
	 * all the interesting cases above.
	 */
}