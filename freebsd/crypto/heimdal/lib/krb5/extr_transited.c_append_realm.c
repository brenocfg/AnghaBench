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
struct tr_realm {struct tr_realm* next; } ;

/* Variables and functions */

__attribute__((used)) static struct tr_realm*
append_realm(struct tr_realm *head, struct tr_realm *r)
{
    struct tr_realm *p;
    if(head == NULL){
	r->next = NULL;
	return r;
    }
    p = head;
    while(p->next) p = p->next;
    p->next = r;
    return head;
}