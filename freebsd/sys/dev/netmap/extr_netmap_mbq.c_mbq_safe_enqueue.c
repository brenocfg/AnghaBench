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
struct mbuf {int dummy; } ;
struct mbq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mbq_enqueue (struct mbq*,struct mbuf*) ; 
 int /*<<< orphan*/  mbq_lock (struct mbq*) ; 
 int /*<<< orphan*/  mbq_unlock (struct mbq*) ; 

void mbq_safe_enqueue(struct mbq *q, struct mbuf *m)
{
    mbq_lock(q);
    __mbq_enqueue(q, m);
    mbq_unlock(q);
}