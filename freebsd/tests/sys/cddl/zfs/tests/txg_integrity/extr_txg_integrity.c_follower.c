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
struct TYPE_3__ {int* permutation; int follower_chunks; } ;
typedef  TYPE_1__ pattern_t ;

/* Variables and functions */
 int NUM_CHUNKS ; 
 int /*<<< orphan*/ * chunk_sems ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ follower_syncs ; 
 int /*<<< orphan*/  my_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outfd ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ phase ; 
 int sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_chunk (TYPE_1__*,int,int) ; 

__attribute__((used)) static void*
follower(void* data)
{
  int perm_idx;
  pattern_t* p_pat = (pattern_t*)data;
/*  printf("Follower started\n");*/
  for(perm_idx = 0; perm_idx < NUM_CHUNKS; perm_idx++)
  {
    int chunk_idx = p_pat->permutation[perm_idx];
    if (perm_idx == NUM_CHUNKS / 2 && phase == follower_syncs){
/*      printf("about to sync in follower\n");*/
      my_sync(outfd);
    }

    if ( (1 << chunk_idx) & p_pat->follower_chunks){
/*      printf("about to pend on semaphore\n");*/
#if USE_THREADS
      if (-1 == sem_wait(&chunk_sems[chunk_idx])){
        perror("sem_wait");
        exit(1);
      }
#endif
/*    printf("about to write chunk in follower\n");*/
      write_chunk(p_pat, chunk_idx, 1);
    }
  }
  return 0;
}