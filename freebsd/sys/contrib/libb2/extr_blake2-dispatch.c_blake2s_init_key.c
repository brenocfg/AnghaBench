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
typedef  int /*<<< orphan*/  blake2s_state ;

/* Variables and functions */
 int blake2s_init_key_ptr (int /*<<< orphan*/ *,size_t,void const*,size_t) ; 

int blake2s_init_key( blake2s_state *S, size_t outlen, const void *key, size_t keylen )
{
  return blake2s_init_key_ptr( S, outlen, key, keylen );
}