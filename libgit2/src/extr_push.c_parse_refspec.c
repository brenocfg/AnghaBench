#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* src; int /*<<< orphan*/  dst; } ;
struct TYPE_7__ {TYPE_3__ refspec; } ;
typedef  TYPE_1__ push_spec ;
typedef  int /*<<< orphan*/  git_push ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ check_lref (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ check_rref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_refspec (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ git_refspec__parse (TYPE_3__*,char const*,int) ; 

__attribute__((used)) static int parse_refspec(git_push *push, push_spec **spec, const char *str)
{
	push_spec *s;

	*spec = NULL;

	s = git__calloc(1, sizeof(*s));
	GIT_ERROR_CHECK_ALLOC(s);

	if (git_refspec__parse(&s->refspec, str, false) < 0) {
		git_error_set(GIT_ERROR_INVALID, "invalid refspec %s", str);
		goto on_error;
	}

	if (s->refspec.src && s->refspec.src[0] != '\0' &&
	    check_lref(push, s->refspec.src) < 0) {
		goto on_error;
	}

	if (check_rref(s->refspec.dst) < 0)
		goto on_error;

	*spec = s;
	return 0;

on_error:
	free_refspec(s);
	return -1;
}