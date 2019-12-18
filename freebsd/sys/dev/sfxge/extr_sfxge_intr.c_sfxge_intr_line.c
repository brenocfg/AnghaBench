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
struct sfxge_evq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfxge_ev_qpoll (struct sfxge_evq*) ; 

__attribute__((used)) static void
sfxge_intr_line(void *arg)
{
	struct sfxge_evq *evq = arg;

	(void)sfxge_ev_qpoll(evq);
}