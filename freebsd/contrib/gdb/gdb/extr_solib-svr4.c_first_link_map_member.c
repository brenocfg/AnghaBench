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
struct link_map_offsets {int /*<<< orphan*/  r_map_size; scalar_t__ r_map_offset; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct link_map_offsets* SVR4_FETCH_LINK_MAP_OFFSETS () ; 
 scalar_t__ debug_base ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
first_link_map_member (void)
{
  CORE_ADDR lm = 0;
  struct link_map_offsets *lmo = SVR4_FETCH_LINK_MAP_OFFSETS ();
  char *r_map_buf = xmalloc (lmo->r_map_size);
  struct cleanup *cleanups = make_cleanup (xfree, r_map_buf);

  read_memory (debug_base + lmo->r_map_offset, r_map_buf, lmo->r_map_size);

  /* Assume that the address is unsigned.  */
  lm = extract_unsigned_integer (r_map_buf, lmo->r_map_size);

  /* FIXME:  Perhaps we should validate the info somehow, perhaps by
     checking r_version for a known version number, or r_state for
     RT_CONSISTENT. */

  do_cleanups (cleanups);

  return (lm);
}