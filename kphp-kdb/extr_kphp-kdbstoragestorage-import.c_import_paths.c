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
 int MAX_DIRS ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_paths (char*,char**) ; 
 int /*<<< orphan*/  import_images (char**,int,int) ; 

__attribute__((used)) static void import_paths (char *paths, int ugmode) {
  char *P[MAX_DIRS];
  int n = get_paths (paths, P);
  if (n >= 0) {
    import_images (P, n, ugmode);
    free (P[0]);
  }
}