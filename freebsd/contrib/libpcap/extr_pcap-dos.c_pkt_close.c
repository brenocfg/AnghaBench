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
struct device {int /*<<< orphan*/ * priv; } ;
typedef  int BOOL ;

/* Variables and functions */
 int PktExitDriver () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int pcap_pkt_debug ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void pkt_close (struct device *dev)
{
  BOOL okay = PktExitDriver();

  if (pcap_pkt_debug > 1)
     fprintf (stderr, "pkt_close(): %d\n", okay);

  if (dev->priv)
     free (dev->priv);
  dev->priv = NULL;
}