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
struct string_list {int nr; TYPE_1__* items; int /*<<< orphan*/  cmp; } ;
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_DUP ; 
 int migrate_one (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  pack_copy_cmp ; 
 scalar_t__ read_dir_paths (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 

__attribute__((used)) static int migrate_paths(struct strbuf *src, struct strbuf *dst)
{
	size_t src_len = src->len, dst_len = dst->len;
	struct string_list paths = STRING_LIST_INIT_DUP;
	int i;
	int ret = 0;

	if (read_dir_paths(&paths, src->buf) < 0)
		return -1;
	paths.cmp = pack_copy_cmp;
	string_list_sort(&paths);

	for (i = 0; i < paths.nr; i++) {
		const char *name = paths.items[i].string;

		strbuf_addf(src, "/%s", name);
		strbuf_addf(dst, "/%s", name);

		ret |= migrate_one(src, dst);

		strbuf_setlen(src, src_len);
		strbuf_setlen(dst, dst_len);
	}

	string_list_clear(&paths, 0);
	return ret;
}