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
 scalar_t__* engine_replica_name ; 
 void* engine_snapshot_replica ; 
 scalar_t__* engine_snapshot_replica_name ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 void* open_replica (scalar_t__*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

int engine_preload_filelist (const char *main_replica_name, const char *aux_replica_name) {
  int l = strlen (main_replica_name);
  if (!aux_replica_name || !*aux_replica_name || !strcmp (aux_replica_name, ".bin") 
     || !strcmp (aux_replica_name, main_replica_name)
     || (!strncmp (aux_replica_name, main_replica_name, l) && !strcmp (aux_replica_name + l, ".bin"))) {
    engine_snapshot_replica_name = engine_replica_name = strdup (main_replica_name);
  } else {
    int l2 = strlen (aux_replica_name);
    if (l2 > 4 && !strcmp (aux_replica_name + l2 - 4, ".bin")) {
      l2 -= 4;
    }
    engine_snapshot_replica_name = strdup (main_replica_name);
    if (aux_replica_name[0] == '.') {
      engine_replica_name = malloc (l + l2 + 1);
      assert (engine_replica_name);
      memcpy (engine_replica_name, main_replica_name, l);
      memcpy (engine_replica_name + l, aux_replica_name, l2);
      engine_replica_name[l+l2] = 0;
    } else {
      engine_replica_name = malloc (l2 + 1);
      assert (engine_replica_name);
      memcpy (engine_replica_name, aux_replica_name, l2);
      engine_replica_name[l2] = 0;
    }
  }
  assert (engine_replica_name && engine_snapshot_replica_name);

  engine_replica = open_replica (engine_replica_name, 0);
  if (!engine_replica) {
    return -1;
  }
  if (engine_snapshot_replica_name == engine_replica_name) {
    engine_snapshot_replica = engine_replica;
  } else {
    engine_snapshot_replica = open_replica (engine_snapshot_replica_name, 1);
    if (!engine_snapshot_replica) {
      return 0;
    }
  }

  return 1;
}