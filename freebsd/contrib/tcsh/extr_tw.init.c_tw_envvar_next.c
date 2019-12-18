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
typedef  int Strbuf ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_appendn (int*,char const*,int) ; 
 int /*<<< orphan*/  USE (int*) ; 
 char const** tw_env ; 

int
tw_envvar_next(struct Strbuf *res, struct Strbuf *dir, int *flags)
{
    const Char *ps;

    USE(flags);
    USE(dir);
    if (tw_env == NULL || *tw_env == NULL)
	return 0;
    for (ps = *tw_env; *ps && *ps != '='; ps++)
	continue;
    Strbuf_appendn(res, *tw_env, ps - *tw_env);
    tw_env++;
    return 1;
}