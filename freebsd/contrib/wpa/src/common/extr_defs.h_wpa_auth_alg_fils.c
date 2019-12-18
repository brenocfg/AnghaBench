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
 int WPA_AUTH_ALG_FILS ; 
 int WPA_AUTH_ALG_FILS_SK_PFS ; 

__attribute__((used)) static inline int wpa_auth_alg_fils(int alg)
{
	return !!(alg & (WPA_AUTH_ALG_FILS | WPA_AUTH_ALG_FILS_SK_PFS));
}