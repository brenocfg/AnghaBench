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
struct nicvf {int /*<<< orphan*/  if_media; } ;

/* Variables and functions */
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10G_SR ; 
 int IFM_10_T ; 
 int IFM_40G_CR4 ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nicvf_media_change ; 
 int /*<<< orphan*/  nicvf_media_status ; 

__attribute__((used)) static int
nicvf_setup_ifmedia(struct nicvf *nic)
{

	ifmedia_init(&nic->if_media, IFM_IMASK, nicvf_media_change,
	    nicvf_media_status);

	/*
	 * Advertise availability of all possible connection types,
	 * even though not all are possible at the same time.
	 */

	ifmedia_add(&nic->if_media, (IFM_ETHER | IFM_10_T | IFM_FDX),
	    0, NULL);
	ifmedia_add(&nic->if_media, (IFM_ETHER | IFM_100_TX | IFM_FDX),
	    0, NULL);
	ifmedia_add(&nic->if_media, (IFM_ETHER | IFM_1000_T | IFM_FDX),
	    0, NULL);
	ifmedia_add(&nic->if_media, (IFM_ETHER | IFM_10G_SR | IFM_FDX),
	    0, NULL);
	ifmedia_add(&nic->if_media, (IFM_ETHER | IFM_40G_CR4 | IFM_FDX),
	    0, NULL);
	ifmedia_add(&nic->if_media, (IFM_ETHER | IFM_AUTO | IFM_FDX),
	    0, NULL);

	ifmedia_set(&nic->if_media, (IFM_ETHER | IFM_AUTO | IFM_FDX));

	return (0);
}