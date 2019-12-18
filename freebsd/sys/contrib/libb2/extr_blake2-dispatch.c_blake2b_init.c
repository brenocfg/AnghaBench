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
typedef  int /*<<< orphan*/  blake2b_state ;

/* Variables and functions */
 int blake2b_init_ptr (int /*<<< orphan*/ *,size_t) ; 

int blake2b_init( blake2b_state *S, size_t outlen )
{
  return blake2b_init_ptr( S, outlen );
}