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
typedef  size_t u8 ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (size_t*,size_t const*,int) ; 

__attribute__((used)) static void aes_ccm_encr_start(size_t L, const u8 *nonce, u8 *a)
{
	/* A_i = Flags | Nonce N | Counter i */
	a[0] = L - 1; /* Flags = L' */
	os_memcpy(&a[1], nonce, 15 - L);
}