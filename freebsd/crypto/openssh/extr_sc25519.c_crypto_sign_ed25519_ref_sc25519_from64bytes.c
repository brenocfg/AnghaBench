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
typedef  int /*<<< orphan*/  sc25519 ;
typedef  unsigned char crypto_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  barrett_reduce (int /*<<< orphan*/ *,unsigned char*) ; 

void sc25519_from64bytes(sc25519 *r, const unsigned char x[64])
{
  int i;
  crypto_uint32 t[64];
  for(i=0;i<64;i++) t[i] = x[i];
  barrett_reduce(r, t);
}