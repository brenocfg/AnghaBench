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
struct mevent {int dummy; } ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int /*<<< orphan*/  EV_ADD ; 
 struct mevent* mevent_add_state (int,int,void (*) (int,int,void*),void*,int /*<<< orphan*/ ) ; 

struct mevent *
mevent_add(int tfd, enum ev_type type,
	   void (*func)(int, enum ev_type, void *), void *param)
{

	return (mevent_add_state(tfd, type, func, param, EV_ADD));
}