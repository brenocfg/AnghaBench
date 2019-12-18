#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct remote_state {TYPE_1__* regs; } ;
struct TYPE_4__ {int support; } ;
struct TYPE_3__ {int /*<<< orphan*/  regnum; int /*<<< orphan*/  in_g_packet; } ;

/* Variables and functions */
 int MAX_REGISTER_SIZE ; 
 int NUM_REGS ; 
#define  PACKET_DISABLE 130 
#define  PACKET_ENABLE 129 
#define  PACKET_SUPPORT_UNKNOWN 128 
 int /*<<< orphan*/  current_regcache ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  regcache_raw_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ remote_protocol_P ; 

__attribute__((used)) static void
remote_prepare_to_store (void)
{
  struct remote_state *rs = get_remote_state ();
  int i;
  char buf[MAX_REGISTER_SIZE];

  /* Make sure the entire registers array is valid.  */
  switch (remote_protocol_P.support)
    {
    case PACKET_DISABLE:
    case PACKET_SUPPORT_UNKNOWN:
      /* Make sure all the necessary registers are cached.  */
      for (i = 0; i < NUM_REGS; i++)
	if (rs->regs[i].in_g_packet)
	  regcache_raw_read (current_regcache, rs->regs[i].regnum, buf);
      break;
    case PACKET_ENABLE:
      break;
    }
}