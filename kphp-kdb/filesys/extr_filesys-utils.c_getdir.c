#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dirent {char const* d_name; } ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  filename; int /*<<< orphan*/  st; } ;
typedef  TYPE_1__ file_t ;
typedef  int /*<<< orphan*/  dyn_mark_t ;
typedef  int /*<<< orphan*/  DIR ;
typedef  int /*<<< orphan*/  A ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_file ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,char const*) ; 
 scalar_t__ lstat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*,...) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 
 void* zmalloc (int) ; 
 int /*<<< orphan*/  zstrdup (char const*) ; 

int getdir (const char *dirname, file_t **R, int sort, int hidden) {
  *R = NULL;
  char path[PATH_MAX];
  int l = snprintf (path, PATH_MAX, "%s/", dirname);
  if (l >= PATH_MAX - 1) { return 0; }
  int max_filename_length = PATH_MAX - 1 - l;
  int n = 0;
  file_t *head = NULL, *p;
  DIR *D = opendir (dirname);
  if (D == NULL) {
    vkprintf (1, "opendir (%s) returns NULL.\n", dirname);
    return 0;
  }
  while (1) {
    errno = 0;
    struct dirent *entry = readdir (D);
    if (entry == NULL) {
      if (errno) {
        kprintf ("getdir (%s) failed. %m\n", dirname);
        exit (1);
      }
      break;
    }
    if (!strcmp (entry->d_name, ".") || !strcmp (entry->d_name, "..")) {
      continue;
    }

    if (!hidden && !strncmp (entry->d_name, ".", 1)) {
      vkprintf (1, "Skip %s in %s.\n", entry->d_name, dirname);
      continue;
    }

    if (strlen (entry->d_name) > max_filename_length) {
      vkprintf (1, "Skipping too long filename (%s/%s).\n", dirname, entry->d_name);
      continue;
    }

    strcpy (path + l, entry->d_name);
    p = zmalloc (sizeof (file_t));
    if (lstat (path, &p->st)) {
      kprintf ("lstat (%s) fail. %m\n", path);
      zfree (p, sizeof (file_t));
      continue;
    }
    p->filename = zstrdup (entry->d_name);
    p->next = head;
    head = p;
    n++;
  }
  closedir (D);
  if (!sort) {
    *R = head;
  } else if (n) {
    int i;
    dyn_mark_t s;
    dyn_mark (s);
    file_t **A = zmalloc (n * sizeof (file_t *));
    p = head;
    for (i = n - 1; i >= 0; i--) {
      A[i] = p;
      p = p->next;
    }
    assert (p == NULL);
    qsort (A, n, sizeof (A[0]), cmp_file);
    A[n-1]->next = NULL;
    for (i = 0; i < n - 1; i++) {
      A[i]->next = A[i+1];
    }
    *R = A[0];
    dyn_release (s);
  }
  return n;
}