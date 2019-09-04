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
struct strbuf {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_common ; 
 int /*<<< orphan*/  common_trie ; 
 int /*<<< orphan*/  init_common_trie () ; 
 int /*<<< orphan*/  replace_dir (struct strbuf*,int,char const*) ; 
 scalar_t__ trie_find (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_common_dir(struct strbuf *buf, int git_dir_len,
			      const char *common_dir)
{
	char *base = buf->buf + git_dir_len;
	init_common_trie();
	if (trie_find(&common_trie, base, check_common, NULL) > 0)
		replace_dir(buf, git_dir_len, common_dir);
}