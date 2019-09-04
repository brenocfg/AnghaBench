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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* absolute_pathdup (char const*) ; 
 char* get_repo_path_1 (struct strbuf*,int*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static char *get_repo_path(const char *repo, int *is_bundle)
{
	struct strbuf path = STRBUF_INIT;
	const char *raw;
	char *canon;

	strbuf_addstr(&path, repo);
	raw = get_repo_path_1(&path, is_bundle);
	canon = raw ? absolute_pathdup(raw) : NULL;
	strbuf_release(&path);
	return canon;
}