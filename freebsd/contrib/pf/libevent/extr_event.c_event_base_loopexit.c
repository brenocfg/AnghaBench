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
struct timeval {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  event_loopexit_cb ; 
 int event_once (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event_base*,struct timeval*) ; 

int
event_base_loopexit(struct event_base *event_base, struct timeval *tv)
{
	return (event_once(-1, EV_TIMEOUT, event_loopexit_cb,
		    event_base, tv));
}