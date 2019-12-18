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
typedef  int /*<<< orphan*/  WSMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * xcalloc (int,int) ; 

__attribute__((used)) static WSMessage *
new_wsmessage (void)
{
  WSMessage *msg = xcalloc (1, sizeof (WSMessage));

  return msg;
}