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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned char* ldns_key_new_frm_fp_hmac_l (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 

unsigned char *
ldns_key_new_frm_fp_hmac(FILE *f, size_t *hmac_size)
{
	return ldns_key_new_frm_fp_hmac_l(f, NULL, hmac_size);
}