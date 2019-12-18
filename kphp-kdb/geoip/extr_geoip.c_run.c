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
 int IP (unsigned int) ; 
 int /*<<< orphan*/  add (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* buff ; 
 int end_parse () ; 
 int /*<<< orphan*/  fgets (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  init_parse () ; 
 int mode ; 
 int /*<<< orphan*/  pack (int /*<<< orphan*/ *) ; 
 unsigned int parse_country () ; 
 unsigned int parse_int () ; 
 unsigned int parse_ip () ; 
 int /*<<< orphan*/  parse_ip_mask (unsigned int*,unsigned int*) ; 
 int parse_string () ; 
 int /*<<< orphan*/  root ; 
 int rules ; 
 int skip_parse () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int total ; 
 int verbosity ; 

void run (void) {
  while (1) {
    if (!fgets (buff, 1000000, stdin)) {
      break;
    }
    init_parse ();
    if (*buff == 10 || *buff == 13 || *buff == '#') {
      continue;
    }
    unsigned start_ip, end_ip, country, region;
    if (!mode) {
      start_ip = parse_ip ();
      assert (!end_parse ());
      end_ip = parse_ip ();
      assert (!end_parse ());
      assert (start_ip == parse_int ());
      assert (!end_parse ());
      assert (end_ip == parse_int ());
      assert (!end_parse ());
      country = parse_country ();
      assert (country);
      assert (!end_parse ());
      assert (parse_string ());
      assert (end_parse ());
    } else if (mode == 1) {
      parse_ip_mask (&start_ip, &end_ip);
      assert (!end_parse ());
      country = parse_int ();
      assert (end_parse ());
    } else if (mode == 2) {
      start_ip = parse_ip ();
      assert (!end_parse ());
      end_ip = parse_ip ();
      assert (!end_parse ());
      country = parse_country ();
      assert (country);
      assert (!end_parse ());
      region = parse_country ();
      assert (!end_parse ());
      assert (skip_parse () == 6);
      assert (end_parse ());
      country = (country << 16) + region;
    } else {
      assert (0);
    }
    if (verbosity >= 3) {
      #define IP(a) (a >> 24) & 0xff, (a >> 16) & 0xff, (a >> 8) & 0xff, (a >> 0) & 0xff
      fprintf (stderr, "add: start_ip = %u.%u.%u.%u, end_ip = %u.%u.%u.%u, color = %d\n", IP(start_ip), IP(end_ip), country);
    }
    add (&root, start_ip, end_ip, country, end_ip - start_ip);
    rules ++;
  }
  if (verbosity) {
    fprintf (stderr, "total %d rules\n", rules);
    fprintf (stderr, "total %d vertices\n", total);
  }
  pack (&root);
}