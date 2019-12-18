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
typedef  enum cryp_algo_mode { ____Placeholder_cryp_algo_mode } cryp_algo_mode ;

/* Variables and functions */
 int CRYP_ALGO_AES_CBC ; 
 int CRYP_ALGO_AES_CTR ; 
 int CRYP_ALGO_AES_ECB ; 
 int CRYP_ALGO_AES_XTS ; 

__attribute__((used)) static int mode_is_aes(enum cryp_algo_mode mode)
{
	return	CRYP_ALGO_AES_ECB == mode ||
		CRYP_ALGO_AES_CBC == mode ||
		CRYP_ALGO_AES_CTR == mode ||
		CRYP_ALGO_AES_XTS == mode;
}