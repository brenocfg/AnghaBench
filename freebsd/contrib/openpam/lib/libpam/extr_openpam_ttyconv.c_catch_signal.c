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

/* Variables and functions */
#define  SIGINT 130 
#define  SIGQUIT 129 
#define  SIGTERM 128 
 int caught_signal ; 

__attribute__((used)) static void
catch_signal(int signo)
{

	switch (signo) {
	case SIGINT:
	case SIGQUIT:
	case SIGTERM:
		caught_signal = signo;
		break;
	}
}