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
 int /*<<< orphan*/  __close_cached_connection (struct cached_connection_*) ; 

int
__close_cached_mp_read_session(struct cached_connection_ *rs)
{

	__close_cached_connection(rs);
	return (0);
}