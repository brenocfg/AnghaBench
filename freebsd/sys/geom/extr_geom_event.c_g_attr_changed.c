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
struct g_provider {int dummy; } ;
struct g_attrchanged_args {char const* attr; struct g_provider* pp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  g_attr_changed_event ; 
 int /*<<< orphan*/  g_free (struct g_attrchanged_args*) ; 
 struct g_attrchanged_args* g_malloc (int,int) ; 
 int g_post_event (int /*<<< orphan*/ ,struct g_attrchanged_args*,int,struct g_provider*,int /*<<< orphan*/ *) ; 

int
g_attr_changed(struct g_provider *pp, const char *attr, int flag)
{
	struct g_attrchanged_args *args;
	int error;

	args = g_malloc(sizeof *args, flag);
	if (args == NULL)
		return (ENOMEM);
	args->pp = pp;
	args->attr = attr;
	error = g_post_event(g_attr_changed_event, args, flag, pp, NULL);
	if (error != 0)
		g_free(args);
	return (error);
}