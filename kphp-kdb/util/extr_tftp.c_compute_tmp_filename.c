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
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 char* output_filename ; 
 int snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_filename ; 

void compute_tmp_filename (void) {
  char a[PATH_MAX];
  assert (snprintf (a, PATH_MAX, "%s.tmp.%ld", output_filename, time (NULL)) < PATH_MAX);
  tmp_filename = strdup (a);
}