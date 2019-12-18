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
typedef  scalar_t__ u_short ;
struct link {int /*<<< orphan*/ * proto_out; int /*<<< orphan*/ * proto_in; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 int NPROTOSTAT ; 
 int PROTO_IN ; 
 TYPE_1__* ProtocolStat ; 

void
link_ProtocolRecord(struct link *l, u_short proto, int type)
{
  int i;

  for (i = 0; i < NPROTOSTAT; i++)
    if (ProtocolStat[i].number == proto || ProtocolStat[i].number == 0) {
      if (type == PROTO_IN)
        l->proto_in[i]++;
      else
        l->proto_out[i]++;
      break;
    }
}