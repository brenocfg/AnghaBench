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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int hash_object_file_literally (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct object_id*,unsigned int) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int hash_literally(struct object_id *oid, int fd, const char *type, unsigned flags)
{
	struct strbuf buf = STRBUF_INIT;
	int ret;

	if (strbuf_read(&buf, fd, 4096) < 0)
		ret = -1;
	else
		ret = hash_object_file_literally(buf.buf, buf.len, type, oid,
						 flags);
	strbuf_release(&buf);
	return ret;
}