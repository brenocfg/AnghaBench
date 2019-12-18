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
 int MAX_MISMATCHED_WORDS ; 
 int /*<<< orphan*/  allowed_deleted_by_rate ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int binlog_check_mode ; 
 int /*<<< orphan*/  creation_date ; 
 int hashtags_enabled ; 
 int import_only_mode ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  return_empty_record_on_error ; 
 int tag_owner ; 
 int universal ; 
 int use_stemmer ; 
 int word_split_utf8 ; 
 int wordfreqs_enabled ; 

int f_parse_option (int val) {
  int x;
  switch (val) {
  case 'A':
    universal = 1;
    break;
  case 'C':
    binlog_check_mode = 1;
    break;
  case 'D':
    creation_date = 0;
    break;
  case 'F':
    return_empty_record_on_error = 0;
    break;
  case 'I':
    import_only_mode = 1;
    break;
  case 'M':
    x = atoi (optarg);
    if (x >= 1 && x <= 5) {
      MAX_MISMATCHED_WORDS = x;
    }
    break;
  case 'O':
    tag_owner = 1;
    break;
  case 'R':
    allowed_deleted_by_rate = optarg;
    break;
  case 'S':
    use_stemmer = 1;
    break;
  case 'U':
    word_split_utf8 = 1;
    break;
  case 'W':
    wordfreqs_enabled = 1;
    break;
  case 't':
    hashtags_enabled = 1;
    break;
  default:
    return -1;
  }
  return 0;
}