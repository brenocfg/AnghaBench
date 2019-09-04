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
struct tl_act_extra {int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  header; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tl_act_extra*) ; 
 int /*<<< orphan*/  tl_query_header_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct tl_act_extra*,int /*<<< orphan*/ ) ; 

void tl_default_act_free (struct tl_act_extra *extra) {
  tl_query_header_delete (extra->header);
  if (!(extra->flags & 1)) {
    return;
  }
  if (extra->flags & 2) {
    free (extra);
  } else {
    zfree (extra, extra->size);
  }
}