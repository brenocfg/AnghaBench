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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int next_input_uchar (unsigned char const* const,int,int*) ; 
 char* symbols64 ; 

int base64_encode (const unsigned char *const input, int ilen, char *output, int olen) {
  int i, j = 0;
  char buf[4];
  for (i = 0; i < ilen; ) {
    int old_i = i;
    int o = next_input_uchar (input, ilen, &i);
    o <<= 8;
    o |= next_input_uchar (input, ilen, &i);
    o <<= 8;
    o |= next_input_uchar (input, ilen, &i);
    int l = i - old_i;
    assert (l > 0 && l <= 3);
    int u;
    for (u = 3; u >= 0; u--) {
      buf[u] = symbols64[o & 63];
      o >>= 6;
    }
    if (l == 1) { 
      buf[2] = buf[3] = '='; 
    }
    else if (l == 2) { 
      buf[3] = '='; 
    }
    if (j + 3 >= olen) {
      return -1;
    }
    memcpy (&output[j], buf, 4);
    j += 4;
  }
  if (j >= olen) {
    return -1;
  }
  output[j++] = 0;
  return 0;
}