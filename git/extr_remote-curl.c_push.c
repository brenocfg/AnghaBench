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
struct discovery {scalar_t__ proto_git; } ;

/* Variables and functions */
 struct discovery* discover_refs (char*,int) ; 
 int /*<<< orphan*/  free_discovery (struct discovery*) ; 
 int push_dav (int,char const**) ; 
 int push_git (struct discovery*,int,char const**) ; 

__attribute__((used)) static int push(int nr_spec, const char **specs)
{
	struct discovery *heads = discover_refs("git-receive-pack", 1);
	int ret;

	if (heads->proto_git)
		ret = push_git(heads, nr_spec, specs);
	else
		ret = push_dav(nr_spec, specs);
	free_discovery(heads);
	return ret;
}