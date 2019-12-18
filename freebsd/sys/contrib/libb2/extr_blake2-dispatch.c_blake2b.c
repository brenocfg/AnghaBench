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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int blake2b_ptr (int /*<<< orphan*/ *,void const*,void const*,size_t,size_t,size_t) ; 

int blake2b( uint8_t *out, const void *in, const void *key, size_t outlen, size_t inlen, size_t keylen )
{
  return blake2b_ptr( out, in, key, outlen, inlen, keylen );
}