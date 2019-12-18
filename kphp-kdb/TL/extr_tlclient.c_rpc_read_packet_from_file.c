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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFF_SIZE ; 
 scalar_t__ P ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 

__attribute__((used)) static int rpc_read_packet_from_file (const char *filename) {
  FILE *f = fopen (filename, "r");
  if (f == NULL) {
    kprintf ("fopen (\"%s\", \"r\") failed. %m\n", filename);
    return -1;
  }
  int r = 0;
  while (r < BUFF_SIZE && fscanf (f, "%x", P+r) == 1) {
    r++;
  }
  fclose (f);
  if (r == BUFF_SIZE) {
    kprintf ("RPC packet is too big.\n");
    return -1;
  }
  return r;
}