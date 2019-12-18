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
typedef  int /*<<< orphan*/  blake2s_state ;

/* Variables and functions */
 int blake2s_update_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

int blake2s_update( blake2s_state *S, const uint8_t *in, size_t inlen )
{
  return blake2s_update_ptr( S, in, inlen );
}