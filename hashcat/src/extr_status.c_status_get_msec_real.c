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
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 double status_get_msec_paused (int /*<<< orphan*/  const*) ; 
 double status_get_msec_running (int /*<<< orphan*/  const*) ; 

double status_get_msec_real (const hashcat_ctx_t *hashcat_ctx)
{
  const double msec_running = status_get_msec_running (hashcat_ctx);
  const double msec_paused  = status_get_msec_paused  (hashcat_ctx);

  const double msec_real = msec_running - msec_paused;

  return msec_real;
}