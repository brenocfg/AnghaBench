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
struct kfs_file_info {scalar_t__ refcnt; struct kfs_file_info* filename; struct kfs_file_info* iv; struct kfs_file_info* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct kfs_file_info*) ; 

__attribute__((used)) static void file_info_decref (struct kfs_file_info *FI) {
  --FI->refcnt;
  assert (FI->refcnt >= 0);
  if (FI->refcnt) {
    return;
  }
  if (FI->start) {
    free (FI->start);
  }
  if (FI->iv) {
    free (FI->iv);
  }
  if (FI->filename) {
    free (FI->filename);
  }
  free (FI);
}