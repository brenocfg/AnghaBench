#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* packet; scalar_t__ hlen; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ WSPipeIn ;
struct TYPE_5__ {struct TYPE_5__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
clear_fifo_packet (WSPipeIn * pipein)
{
  memset (pipein->hdr, 0, sizeof (pipein->hdr));
  pipein->hlen = 0;

  if (pipein->packet == NULL)
    return;

  if (pipein->packet->data)
    free (pipein->packet->data);
  free (pipein->packet);
  pipein->packet = NULL;
}