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
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * log_file ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void log_char (char ch) {
  fputc (ch, stdout);
  if (log_file != NULL) {
    fputc (ch, log_file);
  }
}