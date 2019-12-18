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
struct nd_defrouter {int raflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
#define  ND_RA_FLAG_RTPREF_HIGH 131 
#define  ND_RA_FLAG_RTPREF_LOW 130 
 int ND_RA_FLAG_RTPREF_MASK ; 
#define  ND_RA_FLAG_RTPREF_MEDIUM 129 
#define  ND_RA_FLAG_RTPREF_RSV 128 
 int RTPREF_HIGH ; 
 int RTPREF_INVALID ; 
 int RTPREF_LOW ; 
 int RTPREF_MEDIUM ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
rtpref(struct nd_defrouter *dr)
{
	switch (dr->raflags & ND_RA_FLAG_RTPREF_MASK) {
	case ND_RA_FLAG_RTPREF_HIGH:
		return (RTPREF_HIGH);
	case ND_RA_FLAG_RTPREF_MEDIUM:
	case ND_RA_FLAG_RTPREF_RSV:
		return (RTPREF_MEDIUM);
	case ND_RA_FLAG_RTPREF_LOW:
		return (RTPREF_LOW);
	default:
		/*
		 * This case should never happen.  If it did, it would mean a
		 * serious bug of kernel internal.  We thus always bark here.
		 * Or, can we even panic?
		 */
		log(LOG_ERR, "rtpref: impossible RA flag %x\n", dr->raflags);
		return (RTPREF_INVALID);
	}
	/* NOTREACHED */
}