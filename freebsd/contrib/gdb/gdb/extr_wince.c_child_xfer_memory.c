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
 int remote_read_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int remote_write_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int res ; 

int
child_xfer_memory (CORE_ADDR memaddr, char *our, int len, int write,
		   struct mem_attrib *attrib,
		   struct target_ops *target)
{
  if (len <= 0)
    return 0;

  if (write)
    res = remote_write_bytes (memaddr, our, len);
  else
    res = remote_read_bytes (memaddr, our, len);

  return res;
}