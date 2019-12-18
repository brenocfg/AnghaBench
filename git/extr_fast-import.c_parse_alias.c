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
struct object_entry {int dummy; } ;
struct branch {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (struct object_entry*) ; 
 TYPE_1__ command_buf ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct object_entry* find_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_mark (int /*<<< orphan*/ ,struct object_entry*) ; 
 int /*<<< orphan*/  memset (struct branch*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_mark ; 
 int /*<<< orphan*/  parse_mark () ; 
 int /*<<< orphan*/  parse_objectish_with_prefix (struct branch*,char*) ; 
 int /*<<< orphan*/  read_next_command () ; 
 int /*<<< orphan*/  skip_optional_lf () ; 

__attribute__((used)) static void parse_alias(void)
{
	struct object_entry *e;
	struct branch b;

	skip_optional_lf();
	read_next_command();

	/* mark ... */
	parse_mark();
	if (!next_mark)
		die(_("Expected 'mark' command, got %s"), command_buf.buf);

	/* to ... */
	memset(&b, 0, sizeof(b));
	if (!parse_objectish_with_prefix(&b, "to "))
		die(_("Expected 'to' command, got %s"), command_buf.buf);
	e = find_object(&b.oid);
	assert(e);
	insert_mark(next_mark, e);
}