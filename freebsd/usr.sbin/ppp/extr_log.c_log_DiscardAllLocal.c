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
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  LogALERT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogSetMaskLocal () ; 
 int /*<<< orphan*/  LogWARN ; 
 int MSK (int /*<<< orphan*/ ) ; 

void
log_DiscardAllLocal(u_long *mask)
{
  *mask = MSK(LogERROR) | MSK(LogALERT) | MSK(LogWARN);
  LogSetMaskLocal();
}