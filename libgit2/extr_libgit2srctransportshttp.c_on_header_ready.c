#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  auth_challenges; } ;
struct TYPE_5__ {int /*<<< orphan*/  auth_challenges; } ;
struct TYPE_7__ {char* content_type; char* content_length; char* location; TYPE_2__ server; TYPE_1__ proxy; int /*<<< orphan*/  parse_header_value; int /*<<< orphan*/  parse_header_name; } ;
typedef  TYPE_3__ http_subtransport ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 void* git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_header_ready(http_subtransport *t)
{
	git_buf *name = &t->parse_header_name;
	git_buf *value = &t->parse_header_value;

	if (!strcasecmp("Content-Type", git_buf_cstr(name))) {
		if (t->content_type) {
			git_error_set(GIT_ERROR_NET, "multiple Content-Type headers");
			return -1;
		}

		t->content_type = git__strdup(git_buf_cstr(value));
		GIT_ERROR_CHECK_ALLOC(t->content_type);
	}
	else if (!strcasecmp("Content-Length", git_buf_cstr(name))) {
		if (t->content_length) {
			git_error_set(GIT_ERROR_NET, "multiple Content-Length headers");
			return -1;
		}

		t->content_length = git__strdup(git_buf_cstr(value));
		GIT_ERROR_CHECK_ALLOC(t->content_length);
	}
	else if (!strcasecmp("Proxy-Authenticate", git_buf_cstr(name))) {
		char *dup = git__strdup(git_buf_cstr(value));
		GIT_ERROR_CHECK_ALLOC(dup);

		if (git_vector_insert(&t->proxy.auth_challenges, dup) < 0)
			return -1;
	}
	else if (!strcasecmp("WWW-Authenticate", git_buf_cstr(name))) {
		char *dup = git__strdup(git_buf_cstr(value));
		GIT_ERROR_CHECK_ALLOC(dup);

		if (git_vector_insert(&t->server.auth_challenges, dup) < 0)
			return -1;
	}
	else if (!strcasecmp("Location", git_buf_cstr(name))) {
		if (t->location) {
			git_error_set(GIT_ERROR_NET, "multiple Location headers");
			return -1;
		}

		t->location = git__strdup(git_buf_cstr(value));
		GIT_ERROR_CHECK_ALLOC(t->location);
	}

	return 0;
}