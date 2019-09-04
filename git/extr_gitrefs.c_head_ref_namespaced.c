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
typedef  int (* each_ref_fn ) (int /*<<< orphan*/ ,struct object_id*,int,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  get_git_namespace () ; 
 int /*<<< orphan*/  read_ref_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int head_ref_namespaced(each_ref_fn fn, void *cb_data)
{
	struct strbuf buf = STRBUF_INIT;
	int ret = 0;
	struct object_id oid;
	int flag;

	strbuf_addf(&buf, "%sHEAD", get_git_namespace());
	if (!read_ref_full(buf.buf, RESOLVE_REF_READING, &oid, &flag))
		ret = fn(buf.buf, &oid, flag, cb_data);
	strbuf_release(&buf);

	return ret;
}