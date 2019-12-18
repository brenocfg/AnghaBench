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
typedef  scalar_t__ tls_cipher ;
struct tls_cipher_data {scalar_t__ cipher; } ;

/* Variables and functions */
 size_t NUM_TLS_CIPHER_DATA ; 
 struct tls_cipher_data const* tls_ciphers ; 

const struct tls_cipher_data * tls_get_cipher_data(tls_cipher cipher)
{
	size_t i;
	for (i = 0; i < NUM_TLS_CIPHER_DATA; i++)
		if (tls_ciphers[i].cipher == cipher)
			return &tls_ciphers[i];
	return NULL;
}