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
struct strbuf {char const* buf; } ;
struct object_id {int dummy; } ;
struct object_directory {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_loose_path (struct strbuf*,struct object_id const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static const char *odb_loose_path(struct object_directory *odb,
				  struct strbuf *buf,
				  const struct object_id *oid)
{
	strbuf_reset(buf);
	strbuf_addstr(buf, odb->path);
	strbuf_addch(buf, '/');
	fill_loose_path(buf, oid);
	return buf->buf;
}