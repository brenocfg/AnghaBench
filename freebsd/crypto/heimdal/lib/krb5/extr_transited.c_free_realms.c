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
struct tr_realm {struct tr_realm* realm; struct tr_realm* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tr_realm*) ; 

__attribute__((used)) static void
free_realms(struct tr_realm *r)
{
    struct tr_realm *p;
    while(r){
	p = r;
	r = r->next;
	free(p->realm);
	free(p);
    }
}