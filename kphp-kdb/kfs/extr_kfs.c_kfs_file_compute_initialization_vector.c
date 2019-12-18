#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kfs_file_info {int /*<<< orphan*/ * iv; int /*<<< orphan*/  filename; TYPE_1__* replica; } ;
typedef  TYPE_1__* kfs_replica_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ctx_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* basename (int /*<<< orphan*/ ) ; 
 scalar_t__ compute_iv (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int kfs_file_compute_initialization_vector (struct kfs_file_info *FI) {
  kfs_replica_handle_t R = FI->replica;
  assert (R);
  if (R->ctx_crypto == NULL || FI->iv != NULL) {
    return 0;
  }
  const char *name = basename (FI->filename);
  if (compute_iv (R, name, strlen (name), &FI->iv) < 0) {
    return -1;
  }
  return 0;
}