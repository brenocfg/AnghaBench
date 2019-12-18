#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int metafile_index; } ;
typedef  TYPE_1__ list_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 TYPE_1__** List ; 
 int conv_list_id (int /*<<< orphan*/ ) ; 
 int find_metafile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_list_metafile (list_id_t list_id) {
  int i = conv_list_id (list_id);
  if (i < 0) {
    return -1;
  }
  list_t *L = List[i];
  if (!L) {
    return find_metafile (list_id);
  }
  return L->metafile_index;
}