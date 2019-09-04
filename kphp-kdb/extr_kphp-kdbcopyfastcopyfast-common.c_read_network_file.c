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
 int MAX_RULES ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * network ; 
 scalar_t__ read_rule (char*,int /*<<< orphan*/ *) ; 
 int rules_num ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int read_network_file (char *filename) {
  FILE *f = fopen (filename, "rt");
  if (!f) {
    fprintf (stderr, "can not open network file (error %m)\n");
    return 0;
  }
  char buf[256];
  while (!feof (f)) {
    if (rules_num >= MAX_RULES) {
      fclose (f);
      return rules_num;
    }
    fgets (buf, 255, f);
    rules_num += read_rule(buf, &network[rules_num]);
  }
  if (verbosity) {
    fprintf (stderr, "Read %d rules from network description file\n", rules_num);
  }
  fclose (f);
  return rules_num;
}