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
struct stat {scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
struct TYPE_3__ {scalar_t__ n; scalar_t__ mtime; char** prefix; } ;
typedef  TYPE_1__ hash_entry_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ MAX_DIRS ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_depth0 (int) ; 
 int /*<<< orphan*/  check_depth1 (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 TYPE_1__* get_str_f (scalar_t__*,int) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__*,...) ; 
 int /*<<< orphan*/ * opendir (scalar_t__*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int split_modulo ; 
 int split_rem ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,char*) ; 
 scalar_t__ stat (scalar_t__*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (scalar_t__*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__* walk_path ; 
 int walk_prefix_len ; 

__attribute__((used)) static int walk_rec (DIR *D[5], int D_ID[5], int depth, char *base_path) {
  const int l = strlen (walk_path);
  D[depth] = opendir (walk_path);
  if (D[depth] == NULL) {
    kprintf ("opendir (%s) fail (depth = %d). %m\n", walk_path, depth);
    return -1;
  }
  struct dirent *entry;
  while ( (entry = readdir (D[depth])) != NULL) {
    if (!strcmp (entry->d_name, ".") || !strcmp (entry->d_name, "..")) {
      continue;
    }
    sprintf (walk_path + l, "/%s", entry->d_name);
    struct stat st;
    if (stat (walk_path, &st)) {
      kprintf ("stat (%s) fail. %m\n", walk_path);
      continue;
    }
    if (S_ISDIR(st.st_mode) && depth < 4) {
      errno = 0;
      D_ID[depth + 1] = strtol (entry->d_name, NULL, 10);
      if (errno) {
        continue;
      }
      int skip = 0;
      switch (depth) {
        case 0:
          if (!check_depth0 (D_ID[1])) {
            skip = 1;
          }
          break;
        case 1:
          if (!check_depth1 (D_ID[1] + D_ID[2] * 100)) {
            skip = 1;
          }
          break;
        case 2:
          if (D_ID[3] % split_modulo != split_rem) {
            skip = 1;
          }
          break;
      }
      if (skip) {
        continue;
      }
      walk_rec (D, D_ID, depth + 1, base_path);
    } else if (S_ISREG(st.st_mode) && depth >= 3 && depth <= 4) {
      hash_entry_t *E = get_str_f (walk_path + walk_prefix_len, 1);
      assert (E->n < MAX_DIRS);
      if (E->mtime < st.st_mtime) {
        E->mtime = st.st_mtime;
      }
      E->prefix[E->n++] = base_path;
    }
  }
  walk_path[l] = 0;
  closedir (D[depth]);
  return 0;
}