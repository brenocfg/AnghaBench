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
typedef  enum p2p_go_state { ____Placeholder_p2p_go_state } p2p_go_state ;

/* Variables and functions */
#define  LOCAL_GO 130 
#define  REMOTE_GO 129 
#define  UNKNOWN_GO 128 

__attribute__((used)) static const char * p2p_go_state_text(enum p2p_go_state go_state)
{
	switch (go_state) {
	case UNKNOWN_GO:
		return "unknown";
	case LOCAL_GO:
		return "local";
	case  REMOTE_GO:
		return "remote";
	}

	return "??";
}