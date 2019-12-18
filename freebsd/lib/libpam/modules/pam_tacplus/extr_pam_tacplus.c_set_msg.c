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
struct tac_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tac_close (struct tac_handle*) ; 
 int tac_set_msg (struct tac_handle*,char const*) ; 
 int /*<<< orphan*/  tac_strerror (struct tac_handle*) ; 

__attribute__((used)) static int
set_msg(struct tac_handle *tach, const char *msg)
{
	if (tac_set_msg(tach, msg) == -1) {
		syslog(LOG_CRIT, "tac_set_msg: %s", tac_strerror(tach));
		tac_close(tach);
		return -1;
	}
	return 0;
}