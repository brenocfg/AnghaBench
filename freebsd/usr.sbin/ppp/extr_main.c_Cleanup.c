#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int CleaningUp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 TYPE_1__* SignalBundle ; 
 int /*<<< orphan*/  bundle_Close (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
Cleanup()
{
  SignalBundle->CleaningUp = 1;
  bundle_Close(SignalBundle, NULL, CLOSE_STAYDOWN);
}