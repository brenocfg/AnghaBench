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
struct oidset_iter {int dummy; } ;
struct oidset {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oidset_iter_init (struct oidset*,struct oidset_iter*) ; 
 struct object_id* oidset_iter_next (struct oidset_iter*) ; 
 int /*<<< orphan*/  packet_buf_write (struct strbuf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_common(struct strbuf *req_buf, struct oidset *common)
{
	struct oidset_iter iter;
	const struct object_id *oid;
	oidset_iter_init(common, &iter);

	while ((oid = oidset_iter_next(&iter))) {
		packet_buf_write(req_buf, "have %s\n", oid_to_hex(oid));
	}
}