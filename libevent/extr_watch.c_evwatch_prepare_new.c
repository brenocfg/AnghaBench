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
union evwatch_cb {int /*<<< orphan*/  prepare; } ;
struct evwatch {int dummy; } ;
struct event_base {int dummy; } ;
typedef  int /*<<< orphan*/  evwatch_prepare_cb ;

/* Variables and functions */
 int /*<<< orphan*/  EVWATCH_PREPARE ; 
 struct evwatch* evwatch_new (struct event_base*,union evwatch_cb,void*,int /*<<< orphan*/ ) ; 

struct evwatch *
evwatch_prepare_new(struct event_base *base, evwatch_prepare_cb callback, void *arg)
{
	union evwatch_cb cb = { .prepare = callback };
	return evwatch_new(base, cb, arg, EVWATCH_PREPARE);
}