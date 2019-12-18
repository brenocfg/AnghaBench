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
struct dirlist {scalar_t__ dp_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int OP_ALLDIRS ; 
 int OP_HAVEMASK ; 
 int OP_MAPALL ; 
 int OP_MAPROOT ; 
 int OP_MASK ; 
 int OP_MASKLEN ; 
 int OP_NET ; 
 int OP_SEC ; 
 int opt_flags ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ v4root_phase ; 

__attribute__((used)) static int
check_options(struct dirlist *dp)
{

	if (v4root_phase == 0 && dp == NULL)
	    return (1);
	if ((opt_flags & (OP_MAPROOT | OP_MAPALL)) == (OP_MAPROOT | OP_MAPALL)) {
	    syslog(LOG_ERR, "-mapall and -maproot mutually exclusive");
	    return (1);
	}
	if ((opt_flags & OP_MASK) && (opt_flags & OP_NET) == 0) {
		syslog(LOG_ERR, "-mask requires -network");
		return (1);
	}
	if ((opt_flags & OP_NET) && (opt_flags & OP_HAVEMASK) == 0) {
		syslog(LOG_ERR, "-network requires mask specification");
		return (1);
	}
	if ((opt_flags & OP_MASK) && (opt_flags & OP_MASKLEN)) {
		syslog(LOG_ERR, "-mask and /masklen are mutually exclusive");
		return (1);
	}
	if (v4root_phase > 0 &&
	    (opt_flags &
	     ~(OP_SEC | OP_MASK | OP_NET | OP_HAVEMASK | OP_MASKLEN)) != 0) {
	    syslog(LOG_ERR,"only -sec,-net,-mask options allowed on V4:");
	    return (1);
	}
	if ((opt_flags & OP_ALLDIRS) && dp->dp_left) {
	    syslog(LOG_ERR, "-alldirs has multiple directories");
	    return (1);
	}
	return (0);
}