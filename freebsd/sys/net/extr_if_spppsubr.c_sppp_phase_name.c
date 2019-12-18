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
typedef  enum ppp_phase { ____Placeholder_ppp_phase } ppp_phase ;

/* Variables and functions */
#define  PHASE_AUTHENTICATE 132 
#define  PHASE_DEAD 131 
#define  PHASE_ESTABLISH 130 
#define  PHASE_NETWORK 129 
#define  PHASE_TERMINATE 128 

__attribute__((used)) static const char *
sppp_phase_name(enum ppp_phase phase)
{
	switch (phase) {
	case PHASE_DEAD:	return "dead";
	case PHASE_ESTABLISH:	return "establish";
	case PHASE_TERMINATE:	return "terminate";
	case PHASE_AUTHENTICATE: return "authenticate";
	case PHASE_NETWORK:	return "network";
	}
	return "illegal";
}