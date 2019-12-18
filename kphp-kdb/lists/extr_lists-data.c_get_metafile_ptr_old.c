#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* list_file_offset; } ;
struct TYPE_3__ {int tot_lists; void* list_data_offset; } ;

/* Variables and functions */
 TYPE_2__* FLI_ENTRY_ADJUSTED (int) ; 
 TYPE_1__ Header ; 
 void* MData ; 
 int /*<<< orphan*/  assert (int) ; 
 void* list_id_bytes ; 

__attribute__((used)) static inline void *get_metafile_ptr_old (int p) {
  assert (p >= 0 && p < Header.tot_lists);
  return MData + (FLI_ENTRY_ADJUSTED(p)->list_file_offset - Header.list_data_offset)
#ifdef LISTS_Z
	 + list_id_bytes
#endif	
  ;
}