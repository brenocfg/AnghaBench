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
typedef  size_t u_short ;
typedef  int /*<<< orphan*/  u_fp ;
struct server {size_t filter_nextpt; int /*<<< orphan*/ * filter_error; int /*<<< orphan*/ * filter_soffset; int /*<<< orphan*/ * filter_offset; int /*<<< orphan*/ * filter_delay; } ;
typedef  int /*<<< orphan*/  s_fp ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  LFPTOFP (int /*<<< orphan*/ *) ; 
 size_t NTP_SHIFT ; 

__attribute__((used)) static void
server_data(
	register struct server *server,
	s_fp d,
	l_fp *c,
	u_fp e
	)
{
	u_short i;

	i = server->filter_nextpt;
	if (i < NTP_SHIFT) {
		server->filter_delay[i] = d;
		server->filter_offset[i] = *c;
		server->filter_soffset[i] = LFPTOFP(c);
		server->filter_error[i] = e;
		server->filter_nextpt = (u_short)(i + 1);
	}
}