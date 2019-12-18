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

/* Variables and functions */
 int /*<<< orphan*/  index_iterator_next () ; 
 int /*<<< orphan*/  index_iterator_next_meta () ; 
 int iterator_metafile_number ; 

void index_iterator_init () {
  iterator_metafile_number = -1;
  index_iterator_next_meta ();
  index_iterator_next ();
}