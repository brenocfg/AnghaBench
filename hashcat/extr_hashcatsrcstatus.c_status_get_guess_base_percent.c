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
 int status_get_guess_base_count (int /*<<< orphan*/  const*) ; 
 int status_get_guess_base_offset (int /*<<< orphan*/  const*) ; 

double status_get_guess_base_percent (const hashcat_ctx_t *hashcat_ctx)
{
  const int guess_base_offset = status_get_guess_base_offset (hashcat_ctx);
  const int guess_base_count  = status_get_guess_base_count (hashcat_ctx);

  if (guess_base_count == 0) return 0;

  return ((double) guess_base_offset / (double) guess_base_count) * 100;
}