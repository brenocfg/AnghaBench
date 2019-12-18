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
typedef  int uLongf ;

/* Variables and functions */
 int INT_MAX ; 
 int Z_OK ; 
 int compress2 (unsigned char*,int*,unsigned char*,int,scalar_t__) ; 
 int compressBound (int) ; 
 scalar_t__ compress_level ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 unsigned char* malloc (int) ; 

__attribute__((used)) static void gzip_buff (unsigned char *a, int n, unsigned char **b, int *m) {
  *b = NULL;
  if (compress_level <= 0) {
    kprintf ("compress_level should be strictly positive.\n");
    exit (1);
  }
  uLongf dest = compressBound (n);
  *b = malloc (dest);
  int r = compress2 (*b, &dest, a, n, compress_level);
  if (r != Z_OK) {
    kprintf ("compress2 returns error code %d.\n", r);
    exit (1);
  }
  if (dest > INT_MAX) {
    kprintf ("compressed data is greater than 2G\n");
    exit (1);
  }
  *m = dest;
}