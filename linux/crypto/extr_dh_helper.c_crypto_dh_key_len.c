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
struct dh {int dummy; } ;

/* Variables and functions */
 unsigned int DH_KPP_SECRET_MIN_SIZE ; 
 unsigned int dh_data_size (struct dh const*) ; 

unsigned int crypto_dh_key_len(const struct dh *p)
{
	return DH_KPP_SECRET_MIN_SIZE + dh_data_size(p);
}