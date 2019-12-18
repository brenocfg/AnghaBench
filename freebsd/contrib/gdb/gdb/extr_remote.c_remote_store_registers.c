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
struct remote_state {int /*<<< orphan*/  remote_packet_size; struct packet_reg* regs; int /*<<< orphan*/  sizeof_g_packet; } ;
struct packet_reg {int offset; int /*<<< orphan*/  regnum; scalar_t__ in_g_packet; } ;
struct TYPE_2__ {int support; } ;

/* Variables and functions */
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
#define  PACKET_DISABLE 130 
#define  PACKET_ENABLE 129 
#define  PACKET_SUPPORT_UNKNOWN 128 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin2hex (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  register_bytes_found ; 
 TYPE_1__ remote_protocol_P ; 
 int /*<<< orphan*/  remote_send (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_register_using_P (int) ; 

__attribute__((used)) static void
remote_store_registers (int regnum)
{
  struct remote_state *rs = get_remote_state ();
  char *buf;
  char *regs;
  int i;
  char *p;

  set_thread (PIDGET (inferior_ptid), 1);

  if (regnum >= 0)
    {
      switch (remote_protocol_P.support)
	{
	case PACKET_DISABLE:
	  break;
	case PACKET_ENABLE:
	  if (store_register_using_P (regnum))
	    return;
	  else
	    error ("Protocol error: P packet not recognized by stub");
	case PACKET_SUPPORT_UNKNOWN:
	  if (store_register_using_P (regnum))
	    {
	      /* The stub recognized the 'P' packet.  Remember this.  */
	      remote_protocol_P.support = PACKET_ENABLE;
	      return;
	    }
	  else
	    {
	      /* The stub does not support the 'P' packet.  Use 'G'
	         instead, and don't try using 'P' in the future (it
	         will just waste our time).  */
	      remote_protocol_P.support = PACKET_DISABLE;
	      break;
	    }
	}
    }

  /* Extract all the registers in the regcache copying them into a
     local buffer.  */
  {
    int i;
    regs = alloca (rs->sizeof_g_packet);
    memset (regs, 0, rs->sizeof_g_packet);
    for (i = 0; i < NUM_REGS + NUM_PSEUDO_REGS; i++)
      {
	struct packet_reg *r = &rs->regs[i];
	if (r->in_g_packet)
	  regcache_collect (r->regnum, regs + r->offset);
      }
  }

  /* Command describes registers byte by byte,
     each byte encoded as two hex characters.  */
  buf = alloca (rs->remote_packet_size);
  p = buf;
  *p++ = 'G';
  /* remote_prepare_to_store insures that register_bytes_found gets set.  */
  bin2hex (regs, p, register_bytes_found);
  remote_send (buf, (rs->remote_packet_size));
}