#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ url; } ;
typedef  TYPE_1__ git_proxy_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (scalar_t__) ; 
 int /*<<< orphan*/  GIT_PROXY_OPTIONS_VERSION ; 
 scalar_t__ git__strdup (scalar_t__) ; 
 int /*<<< orphan*/  git_proxy_options_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

int git_proxy_options_dup(git_proxy_options *tgt, const git_proxy_options *src)
{
	if (!src) {
		git_proxy_options_init(tgt, GIT_PROXY_OPTIONS_VERSION);
		return 0;
	}

	memcpy(tgt, src, sizeof(git_proxy_options));
	if (src->url) {
		tgt->url = git__strdup(src->url);
		GIT_ERROR_CHECK_ALLOC(tgt->url);
	}

	return 0;
}