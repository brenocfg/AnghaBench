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
struct traverse_info {int dummy; } ;
struct strbuf {int dummy; } ;
struct name_entry {int /*<<< orphan*/  pathlen; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_make_traverse_path (struct strbuf*,struct traverse_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *traverse_path(const struct traverse_info *info, const struct name_entry *n)
{
	struct strbuf buf = STRBUF_INIT;
	strbuf_make_traverse_path(&buf, info, n->path, n->pathlen);
	return strbuf_detach(&buf, NULL);
}