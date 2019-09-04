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

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,int,int) ; 
 int /*<<< orphan*/  usage () ; 

void add_action (int *act, int i) {
  if (*act) {
    kprintf ("You give two different actions: '%c' and '%c'.\n", *act, i);
    usage ();
  }
  *act = i;
}