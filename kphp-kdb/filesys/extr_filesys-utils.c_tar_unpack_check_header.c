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
 int get_oct (char const*,int,int) ; 
 int /*<<< orphan*/  kprintf (char*,int,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 

__attribute__((used)) static int tar_unpack_check_header (const char header[512]) {
  int i, sum = 0;
  for (i = 0; i < 512; i++) {
    sum += (unsigned char) header[i];
  }
  if (!sum) {
    return 0;
  }
  int x = 0;
  for (i = 148; i < 156; i++) {
    x += (unsigned char) header[i];
  }
  sum += 32 * 8 - x;
  int chksum = get_oct (header, 148, 6);
  if (sum != chksum) {
    kprintf ("broken header, chksum = %d, but sum = %d\n", chksum, sum);
    assert (sum == chksum);
  }
  assert (!memcmp (header + 257, "ustar", 5));
  return 1;
}