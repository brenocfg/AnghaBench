#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZDICT_cover_params_t ;
struct TYPE_6__ {size_t liveJobs; size_t compressedSize; size_t dictSize; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  parameters; int /*<<< orphan*/  dict; } ;
struct TYPE_5__ {size_t totalCompressedSize; size_t dictSize; void* dictContent; } ;
typedef  TYPE_1__ COVER_dictSelection_t ;
typedef  TYPE_2__ COVER_best_t ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 

void COVER_best_finish(COVER_best_t *best, ZDICT_cover_params_t parameters,
                              COVER_dictSelection_t selection) {
  void* dict = selection.dictContent;
  size_t compressedSize = selection.totalCompressedSize;
  size_t dictSize = selection.dictSize;
  if (!best) {
    return;
  }
  {
    size_t liveJobs;
    ZSTD_pthread_mutex_lock(&best->mutex);
    --best->liveJobs;
    liveJobs = best->liveJobs;
    /* If the new dictionary is better */
    if (compressedSize < best->compressedSize) {
      /* Allocate space if necessary */
      if (!best->dict || best->dictSize < dictSize) {
        if (best->dict) {
          free(best->dict);
        }
        best->dict = malloc(dictSize);
        if (!best->dict) {
          best->compressedSize = ERROR(GENERIC);
          best->dictSize = 0;
          ZSTD_pthread_cond_signal(&best->cond);
          ZSTD_pthread_mutex_unlock(&best->mutex);
          return;
        }
      }
      /* Save the dictionary, parameters, and size */
      if (dict) {
        memcpy(best->dict, dict, dictSize);
        best->dictSize = dictSize;
        best->parameters = parameters;
        best->compressedSize = compressedSize;
      }
    }
    if (liveJobs == 0) {
      ZSTD_pthread_cond_broadcast(&best->cond);
    }
    ZSTD_pthread_mutex_unlock(&best->mutex);
  }
}