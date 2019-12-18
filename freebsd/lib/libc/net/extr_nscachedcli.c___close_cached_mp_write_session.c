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
struct cached_connection_ {int dummy; } ;

/* Variables and functions */
 int CET_MP_WRITE_SESSION_CLOSE_NOTIFICATION ; 
 int /*<<< orphan*/  __close_cached_connection (struct cached_connection_*) ; 
 int safe_write (struct cached_connection_*,int*,int) ; 

int
__close_cached_mp_write_session(struct cached_connection_ *ws)
{
	int notification;
	int result;

	notification = CET_MP_WRITE_SESSION_CLOSE_NOTIFICATION;
	result = safe_write(ws, &notification, sizeof(int));
	__close_cached_connection(ws);
	return (0);
}