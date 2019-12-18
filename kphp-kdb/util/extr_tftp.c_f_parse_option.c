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
 void* atoi (char*) ; 
 int blksize ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* optarg ; 
 int /*<<< orphan*/  parse_port_range (char*) ; 
 void* stats_port ; 
 int /*<<< orphan*/  stderr ; 
 int timeout ; 
 int /*<<< orphan*/  usage () ; 

int f_parse_option (int val) {
  switch (val) {
  case 'B':
    blksize = atoi (optarg);
    assert (blksize >= 8 && blksize <= 65464);
    break;
  case 'P':
    stats_port = atoi (optarg);
    break;
  case 'R':
    if (parse_port_range (optarg) < 0) {
      fprintf (stderr, "Illegal -R %s option\n", optarg);
      usage ();
      break;
    }
  case 'T':
    timeout = atoi (optarg);
    assert (timeout >= 1 && timeout <= 255);
    break;
  default:
    fprintf (stderr, "Unimplemented option '%c' (%d)\n", (char) val, val);
    return -1;
  }
  return 0;
}