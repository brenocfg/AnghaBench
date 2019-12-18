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
struct TYPE_2__ {size_t next; } ;

/* Variables and functions */
 size_t head_metafile ; 
 TYPE_1__** metafiles ; 
 int /*<<< orphan*/  unload_metafile (size_t) ; 

int unload_LRU () {
  if (metafiles[head_metafile]->next == head_metafile) {
    return 0;
  }
  unload_metafile (metafiles[head_metafile]->next);
  return 1;
}