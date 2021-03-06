#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int listener; } ;
typedef  TYPE_1__ WSClient ;

/* Variables and functions */

__attribute__((used)) static int
ws_find_client_sock_in_list (void *data, void *needle)
{
  WSClient *client = data;

  return client->listener == (*(int *) needle);
}