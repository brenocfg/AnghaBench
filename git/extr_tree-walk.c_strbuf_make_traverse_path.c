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
struct strbuf {size_t len; scalar_t__ alloc; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  make_traverse_path (scalar_t__,scalar_t__,struct traverse_info const*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 size_t traverse_path_len (struct traverse_info const*,size_t) ; 

void strbuf_make_traverse_path(struct strbuf *out,
			       const struct traverse_info *info,
			       const char *name, size_t namelen)
{
	size_t len = traverse_path_len(info, namelen);

	strbuf_grow(out, len);
	make_traverse_path(out->buf + out->len, out->alloc - out->len,
			   info, name, namelen);
	strbuf_setlen(out, out->len + len);
}