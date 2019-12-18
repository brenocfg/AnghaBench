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
struct block {int dummy; } ;

/* Variables and functions */
 struct block* BLOCK_SUPERBLOCK (struct block*) ; 

__attribute__((used)) static int
block_depth (struct block *block)
{
  int i = 0;
  while ((block = BLOCK_SUPERBLOCK (block)) != NULL)
    {
      i++;
    }
  return i;
}