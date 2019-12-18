#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct file_user_list_entry* dir_entry; int /*<<< orphan*/  legacy_tree; } ;
typedef  TYPE_1__ user_t ;
struct file_user_list_entry {int dummy; } ;
struct TYPE_10__ {int z; } ;
typedef  TYPE_2__ ltree_t ;
struct TYPE_11__ {char* data; } ;
typedef  TYPE_3__ core_mf_t ;
struct TYPE_12__ {int legacy_list_offset; int directory_offset; } ;

/* Variables and functions */
 TYPE_8__* UserHdr ; 
 TYPE_1__* get_user (int) ; 
 char* get_user_metafile (TYPE_1__*) ; 
 int /*<<< orphan*/  index_long_legacy_id ; 
 TYPE_3__* load_user_metafile (int) ; 
 struct file_user_list_entry* lookup_user_directory (int) ; 
 TYPE_2__* ltree_lookup_legacy (int /*<<< orphan*/ ,long long) ; 

int get_local_id_by_legacy_id (int user_id, long long legacy_id) {
  user_t *U = get_user (user_id);
  ltree_t *T;
  struct file_user_list_entry *D;
  char *metafile;

  if (!legacy_id) {
    return 0;
  }

  if (U) {
    T = ltree_lookup_legacy (U->legacy_tree, legacy_id); // may be unstable
    if (T) {
      return T->z;
    }
    D = U->dir_entry;
    metafile = get_user_metafile (U);
  } else {
    D = lookup_user_directory (user_id);
    metafile = 0;
  }

  if (!D) {
    return 0;
  }

  if (!metafile) {
    core_mf_t *M = load_user_metafile (user_id);
    if (!M) {
      return -2;
    }
    metafile = M->data;
  }

  if (!index_long_legacy_id) {
    int a = -1, b, c, *X;
    X = (int *) (metafile + UserHdr->legacy_list_offset);
    b = ((UserHdr->directory_offset - UserHdr->legacy_list_offset) >> 3);
    while (b - a > 1) {
      c = ((a + b) >> 1);
      if (X[2*c] <= legacy_id) {
	a = c;
      } else {
	b = c;
      }
    }
    
    if (a >= 0 && X[2*a] == legacy_id) {
      return X[2*a+1];
    }
  } else {
    int a = -1, b, c;
    int *X;
    X = (int *) (metafile + UserHdr->legacy_list_offset);
    b = ((UserHdr->directory_offset - UserHdr->legacy_list_offset) / 12);
    while (b - a > 1) {
      c = ((a + b) >> 1);
      if (*(long long *)(X + 3*c) <= legacy_id) {
	a = c;
      } else {
	b = c;
      }
    }
    
    if (a >= 0 && *(long long *)(X + 3*a) == legacy_id) {
      return X[3*a+2];
    }
  }
  
  return 0;
}