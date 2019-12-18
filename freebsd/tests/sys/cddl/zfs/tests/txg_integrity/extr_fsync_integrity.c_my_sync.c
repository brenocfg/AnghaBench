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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fsync (int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
my_sync(int fd){
  if (fsync(fd)){
    perror("fsync");
    exit(1);
  }
}