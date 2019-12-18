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
 int /*<<< orphan*/  assert (int) ; 
 void* engine_replica ; 
 scalar_t__ engine_replica_name ; 
 void* engine_snapshot_replica ; 
 scalar_t__ engine_snapshot_replica_name ; 
 scalar_t__ malloc (int) ; 
 void* open_replica (scalar_t__,int) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char const*) ; 
 scalar_t__ strdup (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int filesys_preload_filelist (const char *main_replica_name) {
  int l = strlen (main_replica_name);
  engine_replica_name = strdup (main_replica_name);
  engine_snapshot_replica_name = malloc (l + 6);
  strcpy (engine_snapshot_replica_name, main_replica_name);
  strcpy (engine_snapshot_replica_name + l, "-fake");
  assert (engine_replica_name && engine_snapshot_replica_name);
  engine_replica = open_replica (engine_replica_name, 0);
  if (!engine_replica) {
    return -1;
  }
  engine_snapshot_replica = open_replica (engine_snapshot_replica_name, 1);
  if (!engine_snapshot_replica) {
    return 0;
  }
  return 1;
}