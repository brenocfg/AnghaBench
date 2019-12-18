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
struct hx509_collector {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  hx509_lock ;

/* Variables and functions */

hx509_lock
_hx509_collector_get_lock(struct hx509_collector *c)
{
    return c->lock;
}