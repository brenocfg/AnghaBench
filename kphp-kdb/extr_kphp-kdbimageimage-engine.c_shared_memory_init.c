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
typedef  int /*<<< orphan*/  shm_filename ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SHARED_MEMORY_SIZE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__* SHM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ftruncate (scalar_t__,int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 scalar_t__ max_process_number ; 
 int now ; 
 int port ; 
 int shm_no ; 
 scalar_t__ shm_open (char*,int,int) ; 
 scalar_t__ shm_unlink (char*) ; 
 int snprintf (char*,int,char*,int,int,int,int) ; 

int shared_memory_init (void) {
  int i;
  shm_no = (max_process_number > 0) ? max_process_number : -1;
  assert (shm_no > 0);
  for (i = 0; i < shm_no; i++) {
    char shm_filename[128];
    /* For portable use, name should have an initial slash (/) and contain no embedded slashes. */
    int l = snprintf (shm_filename, sizeof (shm_filename) - 2, "/img%d_%d_%d_%d", getpid (), now, port, i);
    assert (l < (int) sizeof (shm_filename));
    shm_filename[l] = 0;
    SHM[i] = shm_open (shm_filename, O_RDWR | O_CREAT | O_EXCL, 0640);
    if (SHM[i] < 0) {
      kprintf ("Couldn't create share memory object %s\n%m\n", shm_filename);
      shm_no = i;
      return 0;
    }
    ftruncate (SHM[i], MAX_SHARED_MEMORY_SIZE);
    if (shm_unlink (shm_filename) < 0) {
      kprintf ("shm_unlink (%s) failed. %m\n", shm_filename);
      shm_no = i;
      return 0;
    }
  }
  return 1;
}