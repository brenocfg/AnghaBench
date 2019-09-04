#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ metafile; } ;
typedef  TYPE_1__ user ;
struct TYPE_5__ {int multiple_types; } ;

/* Variables and functions */
 scalar_t__ EMPTY__METAFILE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ header ; 

int *user_get_metafile (user *u, int type) {
  assert (header.multiple_types >= 0 && header.multiple_types < 256 && u->metafile);

  if (header.multiple_types != 0) {
    return header.multiple_types == type ? (int *)u->metafile : NULL;
  }

  int *tmp = (int *)u->metafile;
  while (*tmp != 0) {
    if ((*tmp >> 23) == type) {
      return ((int *)u->metafile) + *tmp - (type << 23);
    }
    tmp++;
  }
  return (int *)EMPTY__METAFILE;
}