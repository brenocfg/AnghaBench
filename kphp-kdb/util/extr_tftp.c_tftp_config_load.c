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
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ tftp_file_t ;
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ TFTP_MAX_FILE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 TYPE_1__* get_file_f (char*,int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int strlen (char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 int tot_files ; 
 int /*<<< orphan*/  zmalloc (scalar_t__) ; 
 int /*<<< orphan*/  zstrdup (char*) ; 

int tftp_config_load (const char *config_filename) {
  char s[16384];
  FILE *f = fopen (config_filename, "r");
  if (f == NULL) {
    kprintf ("fail to open config file '%s'. %m\n", config_filename);
    return -1;
  }
  int line = 0, res = 0, fd = -1;
  while (fgets (s, sizeof (s), f) != NULL) {
    line++;
    int l = strlen (s);
    if (l >= sizeof (s) - 1) {
      kprintf ("config line %d is too long\n", line);
      res--;
      break;
    }
    char *ptr;
    char *alias = strtok_r (s, "\t\n ", &ptr);
    if (alias == NULL) {
      continue;
    }
    char *filename = strtok_r (NULL, "\t\n ", &ptr);
    if (filename == NULL) {
      kprintf ("at the %d line of config filename for alias '%s' wasn't given.\n", line, alias);
      res--;
      break;
    }
    int old_tot_files = tot_files;
    tftp_file_t *F = get_file_f (alias, 1);
    if (old_tot_files == tot_files) {
      kprintf ("%d line of config file contains duplicate record for alias '%s'.\n", line, alias);
      res--;
      break;
    }
    int fd = open (filename, O_RDONLY);
    if (fd < 0) {
      kprintf ("fail to open file '%s' for alias '%s' (config line: %d). %m\n", filename, alias, line);
      res--;
      break;
    }
    struct stat st;
    if (fstat (fd, &st) < 0) {
      kprintf ("fstat for file '%s' for alias '%s' failed (config line: %d). %m\n", filename, alias, line);
      res--;
      break;
    }
    F->size = st.st_size;
    if (F->size > TFTP_MAX_FILE_SIZE) {
      kprintf ("file '%s' for alias '%s' is too big (more than %lld bytes) (config line: %d). %m\n", filename, alias, F->size,  line);
      res--;
      break;
    }
    F->data = zmalloc (F->size);
    F->filename = zstrdup (filename);
    ssize_t bytes_read = read (fd, F->data, F->size);
    if (bytes_read != F->size) {
      if (bytes_read < 0) {
        kprintf ("read from file '%s' for alias '%s' failed. %m\n", filename, alias);
        res--;
        break;
      } else {
        kprintf ("read only %lld bytes of expected %lld bytes from file '%s' for alias '%s'.\n", (long long) bytes_read, F->size, filename, alias);
        res--;
        break;
      }
    }
    assert (!close (fd));
    fd = -1;
  }

  if (fd >= 0) {
    close (fd);
    fd = -1;
  }

  if (f) {
    fclose (f);
  }
  return res;
}