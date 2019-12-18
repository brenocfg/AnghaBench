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
struct env {char* str; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envhead ; 
 struct env* malloc (int) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
addenv(char *str)
{
	struct env *env;

	env = malloc(sizeof(struct env));
	env->str = str;
	SLIST_INSERT_HEAD(&envhead, env, next);
}