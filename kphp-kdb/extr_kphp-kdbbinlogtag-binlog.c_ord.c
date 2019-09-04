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
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  kprintf (char*,char) ; 
 char tolower (char) ; 

__attribute__((used)) static unsigned ord (char x) {
  if (!isxdigit (x)) {
    kprintf ("'%c' isn't hex digit\n", x);
    exit (1);
  }
  if (isdigit (x)) {
    return x - 48;
  }
  x = tolower (x);
  return x - 87;
}