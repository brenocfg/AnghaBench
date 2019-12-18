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
struct datalink {int /*<<< orphan*/  cbcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbcp_Down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  datalink_CBCPComplete (struct datalink*) ; 

void
datalink_CBCPFailed(struct datalink *dl)
{
  cbcp_Down(&dl->cbcp);
  datalink_CBCPComplete(dl);
}