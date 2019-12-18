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
struct TYPE_3__ {int docs; int idx_docs; unsigned long long* Idx_Pos; unsigned long long** Pos; int /*<<< orphan*/  mutex_insert; } ;
typedef  TYPE_1__ volume_t ;

/* Variables and functions */
 int STORAGE_ERR_ILLEGAL_LOCAL_ID ; 
 unsigned long long STORAGE_SECRET_MASK ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int doc_hide (volume_t *V, int local_id) {
  pthread_mutex_lock (&V->mutex_insert);
  if (local_id < 1 || local_id > V->docs) {
    pthread_mutex_unlock (&V->mutex_insert);
    return STORAGE_ERR_ILLEGAL_LOCAL_ID;
  }
  unsigned long long *pos;
  if (local_id <= V->idx_docs) {
    pos = &(V->Idx_Pos[local_id]);
  } else {
    int i = local_id - V->idx_docs - 1;
    pos = &(V->Pos[i >> 11][i & 2047]);
  }
  *pos ^= STORAGE_SECRET_MASK;
  pthread_mutex_unlock (&V->mutex_insert);
  return 0;
}