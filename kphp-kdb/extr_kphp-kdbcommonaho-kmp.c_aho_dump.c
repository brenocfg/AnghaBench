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
 int* KA ; 
 int* KB ; 
 int KL ; 
 char* KS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char,int,int) ; 
 int /*<<< orphan*/  stderr ; 

void aho_dump (void) {
  int i;
  for (i = 0; i < KL; i++) {
    fprintf (stderr, "%3d:  '%c'\t%d\t%d\n", i, KS[i] ? KS[i] : '.', KA[i], KB[i]);
  }
}