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
#define  SIGHUP 131 
#define  SIGINT 130 
#define  SIGQUIT 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  quit ; 
 int /*<<< orphan*/  reread_config ; 

__attribute__((used)) static void
signal_handler(int signum)
{

	switch (signum) {
	case SIGHUP:
		reread_config++;
		break;

	case SIGINT:
	case SIGTERM:
	case SIGQUIT:
		quit++;
		break;
	}
}