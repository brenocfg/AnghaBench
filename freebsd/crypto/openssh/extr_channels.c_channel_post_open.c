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
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  Channel ;

/* Variables and functions */
 int /*<<< orphan*/  channel_check_window (struct ssh*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_handle_efd (struct ssh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_handle_rfd (struct ssh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_handle_wfd (struct ssh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
channel_post_open(struct ssh *ssh, Channel *c,
    fd_set *readset, fd_set *writeset)
{
	channel_handle_rfd(ssh, c, readset, writeset);
	channel_handle_wfd(ssh, c, readset, writeset);
	channel_handle_efd(ssh, c, readset, writeset);
	channel_check_window(ssh, c);
}