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
struct forth_stack {int dummy; } ;

/* Variables and functions */
 void* FORTH_PASS ; 

__attribute__((used)) static void *forth_bye (void **IP __attribute__((__unused__)), struct forth_stack *st __attribute__((__unused__))) {
  return FORTH_PASS;
}