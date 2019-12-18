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
struct TYPE_3__ {size_t compressedSize; int /*<<< orphan*/  parameters; scalar_t__ dictSize; int /*<<< orphan*/ * dict; scalar_t__ liveJobs; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ COVER_best_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void COVER_best_init(COVER_best_t *best) {
  if (best==NULL) return; /* compatible with init on NULL */
  (void)ZSTD_pthread_mutex_init(&best->mutex, NULL);
  (void)ZSTD_pthread_cond_init(&best->cond, NULL);
  best->liveJobs = 0;
  best->dict = NULL;
  best->dictSize = 0;
  best->compressedSize = (size_t)-1;
  memset(&best->parameters, 0, sizeof(best->parameters));
}