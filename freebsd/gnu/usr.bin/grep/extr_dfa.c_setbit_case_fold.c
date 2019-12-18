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
typedef  int /*<<< orphan*/  charclass ;

/* Variables and functions */
 scalar_t__ ISLOWER (unsigned int) ; 
 scalar_t__ ISUPPER (unsigned int) ; 
 scalar_t__ case_fold ; 
 int /*<<< orphan*/  setbit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int tolower (unsigned int) ; 
 unsigned int toupper (unsigned int) ; 

__attribute__((used)) static void
setbit_case_fold (unsigned b, charclass c)
{
  setbit (b, c);
  if (case_fold)
    {
      if (ISUPPER (b))
	setbit (tolower (b), c);
      else if (ISLOWER (b))
	setbit (toupper (b), c);
    }
}