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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* show_option (unsigned char) ; 

__attribute__((used)) static void print_options (FILE *f, unsigned char *data, int n) {
  int i;
  for (i = 0; i < n; i++) {
    fprintf (f, "%s '%s'", (i > 0) ? "," : "", show_option (data[i]));
  }
}