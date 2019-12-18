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
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;
typedef  int /*<<< orphan*/  ULONGEST ;
struct TYPE_2__ {scalar_t__ support; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BREAKPOINT_FROM_PC (scalar_t__*,int*) ; 
 scalar_t__ PACKET_DISABLE ; 
 size_t Z_PACKET_SOFTWARE_BP ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexnumstr (char*,int /*<<< orphan*/ ) ; 
 int memory_remove_breakpoint (scalar_t__,char*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 scalar_t__ remote_address_masked (scalar_t__) ; 
 TYPE_1__* remote_protocol_Z ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int target_write_memory (scalar_t__,char*,int) ; 

__attribute__((used)) static int
remote_remove_breakpoint (CORE_ADDR addr, char *contents_cache)
{
  struct remote_state *rs = get_remote_state ();
  int bp_size;

  if (remote_protocol_Z[Z_PACKET_SOFTWARE_BP].support != PACKET_DISABLE)
    {
      char *buf = alloca (rs->remote_packet_size);
      char *p = buf;

      *(p++) = 'z';
      *(p++) = '0';
      *(p++) = ',';

      addr = remote_address_masked (addr);
      p += hexnumstr (p, (ULONGEST) addr);
      BREAKPOINT_FROM_PC (&addr, &bp_size);
      sprintf (p, ",%d", bp_size);

      putpkt (buf);
      getpkt (buf, (rs->remote_packet_size), 0);

      return (buf[0] == 'E');
    }

#ifdef DEPRECATED_REMOTE_BREAKPOINT
  return target_write_memory (addr, contents_cache, sizeof big_break_insn);
#else
  return memory_remove_breakpoint (addr, contents_cache);
#endif /* DEPRECATED_REMOTE_BREAKPOINT */
}