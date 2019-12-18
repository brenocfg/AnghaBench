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
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_current_id (int,struct object_id*,struct object_id*) ; 
 int get_one_patchid (struct object_id*,struct object_id*,struct strbuf*,int) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void generate_id_list(int stable)
{
	struct object_id oid, n, result;
	int patchlen;
	struct strbuf line_buf = STRBUF_INIT;

	oidclr(&oid);
	while (!feof(stdin)) {
		patchlen = get_one_patchid(&n, &result, &line_buf, stable);
		flush_current_id(patchlen, &oid, &result);
		oidcpy(&oid, &n);
	}
	strbuf_release(&line_buf);
}