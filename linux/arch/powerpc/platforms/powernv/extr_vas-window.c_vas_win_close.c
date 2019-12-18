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
struct vas_window {int /*<<< orphan*/  rxwin; scalar_t__ tx_win; int /*<<< orphan*/  num_txwins; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_vinst_win (struct vas_window*) ; 
 int /*<<< orphan*/  poll_window_busy_state (struct vas_window*) ; 
 int /*<<< orphan*/  poll_window_castout (struct vas_window*) ; 
 int /*<<< orphan*/  poll_window_credits (struct vas_window*) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 int /*<<< orphan*/  put_rx_win (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_paste_region (struct vas_window*) ; 
 int /*<<< orphan*/  unpin_close_window (struct vas_window*) ; 
 int /*<<< orphan*/  vas_window_free (struct vas_window*) ; 

int vas_win_close(struct vas_window *window)
{
	if (!window)
		return 0;

	if (!window->tx_win && atomic_read(&window->num_txwins) != 0) {
		pr_devel("Attempting to close an active Rx window!\n");
		WARN_ON_ONCE(1);
		return -EBUSY;
	}

	unmap_paste_region(window);

	clear_vinst_win(window);

	poll_window_busy_state(window);

	unpin_close_window(window);

	poll_window_credits(window);

	poll_window_castout(window);

	/* if send window, drop reference to matching receive window */
	if (window->tx_win)
		put_rx_win(window->rxwin);

	vas_window_free(window);

	return 0;
}