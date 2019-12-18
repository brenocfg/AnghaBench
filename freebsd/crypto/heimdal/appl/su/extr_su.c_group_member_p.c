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
struct group {int /*<<< orphan*/ ** gr_mem; } ;

/* Variables and functions */
 int GROUP_EMPTY ; 
 int GROUP_MEMBER ; 
 int GROUP_MISSING ; 
 int GROUP_NOT_MEMBER ; 
 struct group* getgrnam (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
group_member_p(const char *group, const char *user)
{
    struct group *g;
    int i;
    g = getgrnam(group);
    if(g == NULL)
	return GROUP_MISSING;
    if(g->gr_mem[0] == NULL)
	return GROUP_EMPTY;
    for(i = 0; g->gr_mem[i] != NULL; i++)
	if(strcmp(user, g->gr_mem[i]) == 0)
	    return GROUP_MEMBER;
    return GROUP_NOT_MEMBER;
}