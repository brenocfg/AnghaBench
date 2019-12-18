#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;
typedef  int /*<<< orphan*/  ULONGEST ;
struct TYPE_3__ {scalar_t__ support; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  BREAKPOINT_FROM_PC (scalar_t__*,int*) ; 
 scalar_t__ PACKET_DISABLE ; 
#define  PACKET_ERROR 130 
#define  PACKET_OK 129 
#define  PACKET_UNKNOWN 128 
 scalar_t__ TARGET_BYTE_ORDER ; 
 size_t Z_PACKET_SOFTWARE_BP ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 scalar_t__ big_break_insn ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexnumstr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ little_break_insn ; 
 int memory_insert_breakpoint (scalar_t__,char*) ; 
 int packet_ok (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 scalar_t__ remote_address_masked (scalar_t__) ; 
 TYPE_1__* remote_protocol_Z ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int target_read_memory (scalar_t__,char*,int) ; 
 int target_write_memory (scalar_t__,char*,int) ; 

__attribute__((used)) static int
remote_insert_breakpoint (CORE_ADDR addr, char *contents_cache)
{
  struct remote_state *rs = get_remote_state ();
#ifdef DEPRECATED_REMOTE_BREAKPOINT
  int val;
#endif
  int bp_size;

  /* Try the "Z" s/w breakpoint packet if it is not already disabled.
     If it succeeds, then set the support to PACKET_ENABLE.  If it
     fails, and the user has explicitly requested the Z support then
     report an error, otherwise, mark it disabled and go on. */

  if (remote_protocol_Z[Z_PACKET_SOFTWARE_BP].support != PACKET_DISABLE)
    {
      char *buf = alloca (rs->remote_packet_size);
      char *p = buf;

      addr = remote_address_masked (addr);
      *(p++) = 'Z';
      *(p++) = '0';
      *(p++) = ',';
      p += hexnumstr (p, (ULONGEST) addr);
      BREAKPOINT_FROM_PC (&addr, &bp_size);
      sprintf (p, ",%d", bp_size);

      putpkt (buf);
      getpkt (buf, (rs->remote_packet_size), 0);

      switch (packet_ok (buf, &remote_protocol_Z[Z_PACKET_SOFTWARE_BP]))
	{
	case PACKET_ERROR:
	  return -1;
	case PACKET_OK:
	  return 0;
	case PACKET_UNKNOWN:
	  break;
	}
    }

#ifdef DEPRECATED_REMOTE_BREAKPOINT
  val = target_read_memory (addr, contents_cache, sizeof big_break_insn);

  if (val == 0)
    {
      if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
	val = target_write_memory (addr, (char *) big_break_insn,
				   sizeof big_break_insn);
      else
	val = target_write_memory (addr, (char *) little_break_insn,
				   sizeof little_break_insn);
    }

  return val;
#else
  return memory_insert_breakpoint (addr, contents_cache);
#endif /* DEPRECATED_REMOTE_BREAKPOINT */
}