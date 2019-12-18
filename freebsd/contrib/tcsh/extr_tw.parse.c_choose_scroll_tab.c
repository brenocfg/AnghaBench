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
struct scroll_tab_list {int /*<<< orphan*/ * element; struct scroll_tab_list* next; } ;
struct Strbuf {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ **) ; 
 size_t curchoice ; 
 int /*<<< orphan*/  fcompare ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ) ; 
 struct scroll_tab_list* scroll_tab ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/ ** xmalloc (int) ; 

__attribute__((used)) static void
choose_scroll_tab(struct Strbuf *exp_name, int cnt)
{
    struct scroll_tab_list *loop;
    int tmp = cnt;
    Char **ptr;

    ptr = xmalloc(sizeof(Char *) * cnt);
    cleanup_push(ptr, xfree);

    for(loop = scroll_tab; loop && (tmp >= 0); loop = loop->next)
	ptr[--tmp] = loop->element;

    qsort(ptr, cnt, sizeof(Char *), fcompare);

    exp_name->len = 0;
    Strbuf_append(exp_name, ptr[curchoice]);
    Strbuf_terminate(exp_name);
    cleanup_until(ptr);
}