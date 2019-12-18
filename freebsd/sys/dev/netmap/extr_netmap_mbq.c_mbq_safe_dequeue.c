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
 struct mbuf* __mbq_dequeue (struct mbq*) ; 
 int /*<<< orphan*/  mbq_lock (struct mbq*) ; 
 int /*<<< orphan*/  mbq_unlock (struct mbq*) ; 

struct mbuf *mbq_safe_dequeue(struct mbq *q)
{
    struct mbuf *ret;

    mbq_lock(q);
    ret =  __mbq_dequeue(q);
    mbq_unlock(q);

    return ret;
}