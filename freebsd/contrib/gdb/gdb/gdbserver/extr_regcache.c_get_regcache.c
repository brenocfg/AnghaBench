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
struct thread_info {int dummy; } ;
struct inferior_regcache_data {int registers_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fetch_inferior_registers (int /*<<< orphan*/ ) ; 
 scalar_t__ inferior_regcache_data (struct thread_info*) ; 

__attribute__((used)) static struct inferior_regcache_data *
get_regcache (struct thread_info *inf, int fetch)
{
  struct inferior_regcache_data *regcache;

  regcache = (struct inferior_regcache_data *) inferior_regcache_data (inf);

  if (regcache == NULL)
    fatal ("no register cache");

  /* FIXME - fetch registers for INF */
  if (fetch && regcache->registers_valid == 0)
    {
      fetch_inferior_registers (0);
      regcache->registers_valid = 1;
    }

  return regcache;
}