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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  expand_notes_ref (struct strbuf*) ; 
 scalar_t__ get_oid (int /*<<< orphan*/ ,struct object_id*) ; 

void expand_loose_notes_ref(struct strbuf *sb)
{
	struct object_id object;

	if (get_oid(sb->buf, &object)) {
		/* fallback to expand_notes_ref */
		expand_notes_ref(sb);
	}
}