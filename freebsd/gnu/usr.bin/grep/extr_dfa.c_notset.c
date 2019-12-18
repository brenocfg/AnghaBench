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
typedef  int /*<<< orphan*/ * charclass ;

/* Variables and functions */
 int CHARCLASS_INTS ; 

__attribute__((used)) static void
notset (charclass s)
{
  int i;

  for (i = 0; i < CHARCLASS_INTS; ++i)
    s[i] = ~s[i];
}