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
struct grep_source {int /*<<< orphan*/  identifier; int /*<<< orphan*/  name; int /*<<< orphan*/  buf; int /*<<< orphan*/  size; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grep_read_lock () ; 
 int /*<<< orphan*/  grep_read_unlock () ; 
 char* oid_to_hex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_object_file (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grep_source_load_oid(struct grep_source *gs)
{
	enum object_type type;

	grep_read_lock();
	gs->buf = read_object_file(gs->identifier, &type, &gs->size);
	grep_read_unlock();

	if (!gs->buf)
		return error(_("'%s': unable to read %s"),
			     gs->name,
			     oid_to_hex(gs->identifier));
	return 0;
}