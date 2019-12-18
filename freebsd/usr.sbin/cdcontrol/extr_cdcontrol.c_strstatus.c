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
#define  ASTS_COMPLETED 133 
#define  ASTS_ERROR 132 
#define  ASTS_INVALID 131 
#define  ASTS_PAUSED 130 
#define  ASTS_PLAYING 129 
#define  ASTS_VOID 128 

__attribute__((used)) static const char *
strstatus(int sts)
{
	switch (sts) {
	case ASTS_INVALID:	return ("invalid");
	case ASTS_PLAYING:	return ("playing");
	case ASTS_PAUSED:	return ("paused");
	case ASTS_COMPLETED:	return ("completed");
	case ASTS_ERROR:	return ("error");
	case ASTS_VOID:		return ("void");
	default:		return ("??");
	}
}