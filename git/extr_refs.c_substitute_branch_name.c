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
struct repository {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int repo_interpret_branch_name (struct repository*,char const*,int,struct strbuf*,int /*<<< orphan*/ ) ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 

__attribute__((used)) static char *substitute_branch_name(struct repository *r,
				    const char **string, int *len)
{
	struct strbuf buf = STRBUF_INIT;
	int ret = repo_interpret_branch_name(r, *string, *len, &buf, 0);

	if (ret == *len) {
		size_t size;
		*string = strbuf_detach(&buf, &size);
		*len = size;
		return (char *)*string;
	}

	return NULL;
}