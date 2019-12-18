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
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

enum target_signal
target_signal_from_command (int num)
{
  if (num >= 1 && num <= 15)
    return (enum target_signal) num;
  error ("Only signals 1-15 are valid as numeric signals.\n\
Use \"info signals\" for a list of symbolic signals.");
}