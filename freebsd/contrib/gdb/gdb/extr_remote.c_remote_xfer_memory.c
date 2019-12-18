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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  gdbarch_remote_translate_xfer_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int remote_read_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int remote_write_bytes (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
remote_xfer_memory (CORE_ADDR mem_addr, char *buffer, int mem_len,
		    int should_write, struct mem_attrib *attrib,
		    struct target_ops *target)
{
  CORE_ADDR targ_addr;
  int targ_len;
  int res;

  /* Should this be the selected frame?  */
  gdbarch_remote_translate_xfer_address (current_gdbarch, current_regcache,
					 mem_addr, mem_len,
					 &targ_addr, &targ_len);
  if (targ_len <= 0)
    return 0;

  if (should_write)
    res = remote_write_bytes (targ_addr, buffer, targ_len);
  else
    res = remote_read_bytes (targ_addr, buffer, targ_len);

  return res;
}