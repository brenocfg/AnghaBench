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
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  transaction_dirname ; 

__attribute__((used)) static void set_transaction_dirname (char *p) {
  int i = strlen (p);
  if (i == 0) {
    p = ".";
  } else if (p[i-1] == '/') {
    p[i - 1] = 0;
  }
  transaction_dirname = strdup (p);
}