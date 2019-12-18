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
struct vmctx {int dummy; } ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int PM1_PWRBTN_STS ; 
 int pm1_status ; 
 int /*<<< orphan*/  pm_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_update (struct vmctx*) ; 

__attribute__((used)) static void
power_button_handler(int signal, enum ev_type type, void *arg)
{
	struct vmctx *ctx;

	ctx = arg;
	pthread_mutex_lock(&pm_lock);
	if (!(pm1_status & PM1_PWRBTN_STS)) {
		pm1_status |= PM1_PWRBTN_STS;
		sci_update(ctx);
	}
	pthread_mutex_unlock(&pm_lock);
}