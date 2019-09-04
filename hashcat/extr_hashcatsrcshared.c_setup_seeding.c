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
typedef  unsigned int u32 ;
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int /*<<< orphan*/  srand (unsigned int const) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

void setup_seeding (const bool rp_gen_seed_chgd, const u32 rp_gen_seed)
{
  if (rp_gen_seed_chgd == true)
  {
    srand (rp_gen_seed);
  }
  else
  {
    const time_t ts = time (NULL); // don't tell me that this is an insecure seed

    srand ((unsigned int) ts);
  }
}