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
struct TYPE_2__ {char* attributes; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  apply; int /*<<< orphan*/  check; int /*<<< orphan*/  shutdown; int /*<<< orphan*/ * initialize; int /*<<< orphan*/  version; } ;
struct crlf_filter {TYPE_1__ f; } ;
typedef  int /*<<< orphan*/  git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_VERSION ; 
 int /*<<< orphan*/  crlf_apply ; 
 int /*<<< orphan*/  crlf_check ; 
 int /*<<< orphan*/  crlf_cleanup ; 
 struct crlf_filter* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_filter_free ; 

git_filter *git_crlf_filter_new(void)
{
	struct crlf_filter *f = git__calloc(1, sizeof(struct crlf_filter));
	if (f == NULL)
		return NULL;

	f->f.version = GIT_FILTER_VERSION;
	f->f.attributes = "crlf eol text";
	f->f.initialize = NULL;
	f->f.shutdown = git_filter_free;
	f->f.check    = crlf_check;
	f->f.apply    = crlf_apply;
	f->f.cleanup  = crlf_cleanup;

	return (git_filter *)f;
}