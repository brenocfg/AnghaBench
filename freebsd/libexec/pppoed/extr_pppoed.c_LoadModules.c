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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int kldload (char const*) ; 
 int modfind (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
LoadModules(void)
{
  const char *module[] = { "netgraph", "ng_socket", "ng_ether", "ng_pppoe" };
  int f;

  for (f = 0; f < sizeof module / sizeof *module; f++)
    if (modfind(module[f]) == -1 && kldload(module[f]) == -1) {
      fprintf(stderr, "kldload: %s: %s\n", module[f], strerror(errno));
      return 0;
    }

  return 1;
}