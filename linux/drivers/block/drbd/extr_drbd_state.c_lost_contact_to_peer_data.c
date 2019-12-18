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
typedef  enum drbd_disk_state { ____Placeholder_drbd_disk_state } drbd_disk_state ;

/* Variables and functions */
 int D_DISKLESS ; 
 int D_FAILED ; 
 int D_INCONSISTENT ; 
 int D_OUTDATED ; 
 int D_UNKNOWN ; 

__attribute__((used)) static bool lost_contact_to_peer_data(enum drbd_disk_state os, enum drbd_disk_state ns)
{
	if ((os >= D_INCONSISTENT && os != D_UNKNOWN && os != D_OUTDATED)
	&&  (ns < D_INCONSISTENT || ns == D_UNKNOWN || ns == D_OUTDATED))
		return true;

	/* Scenario, starting with normal operation
	 * Connected Primary/Secondary UpToDate/UpToDate
	 * NetworkFailure Primary/Unknown UpToDate/DUnknown (frozen)
	 * ...
	 * Connected Primary/Secondary UpToDate/Diskless (resumed; needs to bump uuid!)
	 */
	if (os == D_UNKNOWN
	&&  (ns == D_DISKLESS || ns == D_FAILED || ns == D_OUTDATED))
		return true;

	return false;
}