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
 int CRPT_EVENT ; 
 int PEER_EVENT ; 
 int /*<<< orphan*/  crypto_codes ; 
 char const* getcode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_codes ; 
 int /*<<< orphan*/  sys_codes ; 

const char *
eventstr(
	int num
	)
{
	if (num & PEER_EVENT)
		return (getcode(num & ~PEER_EVENT, peer_codes));
#ifdef AUTOKEY
	else if (num & CRPT_EVENT)
		return (getcode(num & ~CRPT_EVENT, crypto_codes));
#endif	/* AUTOKEY */
	else
		return (getcode(num, sys_codes));
}