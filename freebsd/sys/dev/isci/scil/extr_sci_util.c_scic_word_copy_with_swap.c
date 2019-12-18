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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SWAP_DWORD (int /*<<< orphan*/ ) ; 

void scic_word_copy_with_swap(
   U32 *destination,
   U32 *source,
   U32 word_count
)
{
   while (word_count--)
   {
      *destination = SCIC_SWAP_DWORD(*source);

      source++;
      destination++;
   }
}