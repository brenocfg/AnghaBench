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
struct ecdh {unsigned int key_size; } ;

/* Variables and functions */
 unsigned int ECDH_KPP_SECRET_MIN_SIZE ; 

unsigned int crypto_ecdh_key_len(const struct ecdh *params)
{
	return ECDH_KPP_SECRET_MIN_SIZE + params->key_size;
}