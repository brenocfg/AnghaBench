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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  OBJ_NONE ; 
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_object_entry (struct object_id*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_preferred_base (struct object_id*) ; 
 int /*<<< orphan*/  add_preferred_base_object (char const*) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 scalar_t__ parse_oid_hex (char*,struct object_id*,char const**) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static void read_object_list_from_stdin(void)
{
	char line[GIT_MAX_HEXSZ + 1 + PATH_MAX + 2];
	struct object_id oid;
	const char *p;

	for (;;) {
		if (!fgets(line, sizeof(line), stdin)) {
			if (feof(stdin))
				break;
			if (!ferror(stdin))
				die("BUG: fgets returned NULL, not EOF, not error!");
			if (errno != EINTR)
				die_errno("fgets");
			clearerr(stdin);
			continue;
		}
		if (line[0] == '-') {
			if (get_oid_hex(line+1, &oid))
				die(_("expected edge object ID, got garbage:\n %s"),
				    line);
			add_preferred_base(&oid);
			continue;
		}
		if (parse_oid_hex(line, &oid, &p))
			die(_("expected object ID, got garbage:\n %s"), line);

		add_preferred_base_object(p + 1);
		add_object_entry(&oid, OBJ_NONE, p + 1, 0);
	}
}