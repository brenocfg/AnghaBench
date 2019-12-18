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
 int SCMD_HMAC_CTRL_DIV2 ; 
 int SCMD_HMAC_CTRL_IPSEC_96BIT ; 
 int SCMD_HMAC_CTRL_NO_TRUNC ; 
 int SCMD_HMAC_CTRL_TRUNC_RFC4366 ; 

__attribute__((used)) static int
ccr_hmac_ctrl(unsigned int hashsize, unsigned int authsize)
{

	if (authsize == 10)
		return (SCMD_HMAC_CTRL_TRUNC_RFC4366);
	if (authsize == 12)
		return (SCMD_HMAC_CTRL_IPSEC_96BIT);
	if (authsize == hashsize / 2)
		return (SCMD_HMAC_CTRL_DIV2);
	return (SCMD_HMAC_CTRL_NO_TRUNC);
}