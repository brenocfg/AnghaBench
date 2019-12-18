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
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;
struct object_directory {int /*<<< orphan*/  path; } ;
struct alternate_refs_data {int /*<<< orphan*/  data; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  is_directory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_alternate_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_realpath (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (struct strbuf*,char*) ; 

__attribute__((used)) static int refs_from_alternate_cb(struct object_directory *e,
				  void *data)
{
	struct strbuf path = STRBUF_INIT;
	size_t base_len;
	struct alternate_refs_data *cb = data;

	if (!strbuf_realpath(&path, e->path, 0))
		goto out;
	if (!strbuf_strip_suffix(&path, "/objects"))
		goto out;
	base_len = path.len;

	/* Is this a git repository with refs? */
	strbuf_addstr(&path, "/refs");
	if (!is_directory(path.buf))
		goto out;
	strbuf_setlen(&path, base_len);

	read_alternate_refs(path.buf, cb->fn, cb->data);

out:
	strbuf_release(&path);
	return 0;
}