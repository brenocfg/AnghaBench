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
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 

__attribute__((used)) static int
openfirm_checkid(phandle_t sid, phandle_t tid)
{

	for (; sid != 0; sid = OF_peer(sid))
		if (sid == tid || openfirm_checkid(OF_child(sid), tid))
			return (1);

	return (0);
}