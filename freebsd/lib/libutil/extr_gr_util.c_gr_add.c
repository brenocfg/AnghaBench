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
struct group {int dummy; } ;

/* Variables and functions */
 struct group* grcopy (struct group const*,char*,char const*,int) ; 
 size_t grmemlen (struct group const*,char const*,int*) ; 
 char* malloc (size_t) ; 

struct group *
gr_add(const struct group *gr, const char *newmember)
{
	char *mem;
	size_t len;
	int num_mem;

	num_mem = 0;
	len = grmemlen(gr, newmember, &num_mem);
	/* Create new group and copy old group into it. */
	if ((mem = malloc(len)) == NULL)
		return (NULL);
	return (grcopy(gr, mem, newmember, num_mem));
}