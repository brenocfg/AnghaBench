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
struct bundle {size_t phase; } ;

/* Variables and functions */
 size_t PHASE_TERMINATE ; 
 char const** PhaseNames ; 

const char *
bundle_PhaseName(struct bundle *bundle)
{
  return bundle->phase <= PHASE_TERMINATE ?
    PhaseNames[bundle->phase] : "unknown";
}