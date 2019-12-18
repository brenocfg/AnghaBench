#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int shift; } ;
typedef  TYPE_1__ hash_t ;
typedef  int hash_key_t ;
typedef  int apr_size_t ;

/* Variables and functions */

__attribute__((used)) static apr_size_t
hash_to_index(hash_t *hash, hash_key_t adler32)
{
  return (adler32 * 0xd1f3da69) >> hash->shift;
}