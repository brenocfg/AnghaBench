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
struct targ_gather_extra {scalar_t__ magic; int extra_start; int extra_end; int /*<<< orphan*/  slice_limit; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ TARG_GATHER_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ regenerate_search_extra (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int targ_generate_new_key (char *buff, char *key, int key_len, void *E) {
  struct targ_gather_extra *extra = E;
  assert (extra->magic == TARG_GATHER_MAGIC);
  int l = 0;
  memcpy (buff + l, key, extra->extra_start);
  l += extra->extra_start;
  l += regenerate_search_extra (buff + l, extra->flags, extra->slice_limit);
  memcpy (buff + l, key + extra->extra_end, key_len - extra->extra_end);
  l += key_len - extra->extra_end;
  return l;
}