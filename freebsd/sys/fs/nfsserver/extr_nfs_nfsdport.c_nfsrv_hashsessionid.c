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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFSX_V4SESSIONID ; 
 int /*<<< orphan*/  hash32_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t
nfsrv_hashsessionid(uint8_t *sessionid)
{
	uint32_t hashval;

	hashval = hash32_buf(sessionid, NFSX_V4SESSIONID, 0);
	return (hashval);
}