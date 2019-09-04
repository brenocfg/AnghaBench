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
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int strlen (char const*) ; 

void row (const char *key) {
  int i = strlen (key) + 1;
  printf ("%s:", key);
  while (i < 17) {
    putchar (' ');
    i++;
  }
}