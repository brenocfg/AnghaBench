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
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  writeout (char*,scalar_t__) ; 
 int /*<<< orphan*/  writeout_char (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writeout_string (char *str) {
  if (!str) {
    writeout_char (0);
  } else {
    writeout (str, strlen (str) + 1);
  }
}