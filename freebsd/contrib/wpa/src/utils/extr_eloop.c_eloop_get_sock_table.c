#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eloop_sock_table {int dummy; } ;
typedef  int eloop_event_type ;
struct TYPE_2__ {struct eloop_sock_table exceptions; struct eloop_sock_table writers; struct eloop_sock_table readers; } ;

/* Variables and functions */
#define  EVENT_TYPE_EXCEPTION 130 
#define  EVENT_TYPE_READ 129 
#define  EVENT_TYPE_WRITE 128 
 TYPE_1__ eloop ; 

__attribute__((used)) static struct eloop_sock_table *eloop_get_sock_table(eloop_event_type type)
{
	switch (type) {
	case EVENT_TYPE_READ:
		return &eloop.readers;
	case EVENT_TYPE_WRITE:
		return &eloop.writers;
	case EVENT_TYPE_EXCEPTION:
		return &eloop.exceptions;
	}

	return NULL;
}