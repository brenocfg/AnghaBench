#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int warn_bad_backups_which_could_be_deleted; int warn_redundant_good_backups; void* check_level; int /*<<< orphan*/  check_type; void* shorter_middle_log_level; void* shorter_last_log_level; } ;

/* Variables and functions */
 char* BACKUP_ALL_SUBOPTIONS ; 
 TYPE_1__ backups_features ; 
 char* backups_suboptions ; 
 int /*<<< orphan*/  bc_full ; 
 int /*<<< orphan*/  bc_partial ; 
 int /*<<< orphan*/  isupper (char const) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 void* ll_error ; 
 void* ll_warning ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int backup_parse_suboptions (void) {
  if (backups_suboptions == NULL) {
    kprintf ("Backup suboptions wasn't specified (use -B switch).\n");
    return -1;
  }
  if (!strcmp (backups_suboptions, "all")) {
    backups_suboptions = BACKUP_ALL_SUBOPTIONS ;
  }
  const char *s;
  int bc_opts = 0;
  for (s = backups_suboptions; *s; s++) {
    switch (*s) {
    case 'd':
      backups_features.warn_bad_backups_which_could_be_deleted = 1;
    break;
    case 'r':
      backups_features.warn_redundant_good_backups = 1;
    break;
    case 'L':
    case 'l':
      backups_features.shorter_last_log_level = isupper (*s) ? ll_error : ll_warning;
    break;
    case 'M':
    case 'm':
      backups_features.shorter_middle_log_level = isupper (*s) ? ll_error : ll_warning;
    break;
    case 'F':
    case 'f':
      bc_opts++;
      backups_features.check_type = bc_full;
      backups_features.check_level = isupper (*s) ? ll_error : ll_warning;
    break;
    case 'p':
    case 'P':
      bc_opts++;
      backups_features.check_type = bc_partial;
      backups_features.check_level = isupper (*s) ? ll_error : ll_warning;
    break;
    default:
      kprintf ("Unimplemented suboption: '%c'\n", *s);
      return -1;
    }
  }

  if (bc_opts != 1) {
    kprintf ("Backup suboptions should contain exactly one option from the list ['f', 'F', 'p', 'P'] or equal to 'all'.\n");
    return -1;
  }

  return 0;
}