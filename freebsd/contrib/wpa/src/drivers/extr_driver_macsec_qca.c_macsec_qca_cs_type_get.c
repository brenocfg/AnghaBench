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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  fal_cipher_suite_e ;

/* Variables and functions */
 scalar_t__ CS_ID_GCM_AES_128 ; 
 scalar_t__ CS_ID_GCM_AES_256 ; 
 int /*<<< orphan*/  FAL_CIPHER_SUITE_AES_GCM_128 ; 
 int /*<<< orphan*/  FAL_CIPHER_SUITE_AES_GCM_256 ; 
 int /*<<< orphan*/  FAL_CIPHER_SUITE_MAX ; 

__attribute__((used)) static fal_cipher_suite_e macsec_qca_cs_type_get(u64 cs)
{
	if (cs == CS_ID_GCM_AES_128)
		return FAL_CIPHER_SUITE_AES_GCM_128;
	if (cs == CS_ID_GCM_AES_256)
		return FAL_CIPHER_SUITE_AES_GCM_256;
	return FAL_CIPHER_SUITE_MAX;
}