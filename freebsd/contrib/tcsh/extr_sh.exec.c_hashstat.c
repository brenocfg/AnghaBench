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
typedef  int /*<<< orphan*/ * command ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 int hashdebug ; 
 int /*<<< orphan*/  hashlength ; 
 int hashwidth ; 
 scalar_t__ havhash ; 
 int hits ; 
 int misses ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ,int,...) ; 

void
hashstat(Char **v, struct command *c)
{
    USE(c);
    USE(v);
#ifdef FASTHASH 
   if (havhash && hashlength && hashwidth)
      xprintf(CGETS(13, 2, "%d hash buckets of %d bits each\n"),
	      hashlength, hashwidth*8);
   if (hashdebug)
      xprintf(CGETS(13, 3, "debug mask = 0x%08x\n"), hashdebug);
#endif /* FASTHASH */
#ifdef VFORK
   if (hits + misses)
      xprintf(CGETS(13, 4, "%d hits, %d misses, %d%%\n"),
	      hits, misses, 100 * hits / (hits + misses));
#endif
}