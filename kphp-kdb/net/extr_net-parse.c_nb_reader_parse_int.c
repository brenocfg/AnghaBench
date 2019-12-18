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
struct nb_reader {int dummy; } ;

/* Variables and functions */
 scalar_t__ isdigit (int) ; 
 int nb_reader_getc (struct nb_reader*) ; 

int nb_reader_parse_int (struct nb_reader *I, int *x, int *c) {
  int sgn = 0, r = 0;
  *c = nb_reader_getc (I);
  if (*c == '-') {
    sgn = 1;
    *c = nb_reader_getc (I);
  } 
  
  if (*c < 0 || !isdigit(*c)) {
    return 0; 
  }
  
  do {
    if (r > 0x7fffffff / 10) {
      return 0;
    }
    r = r * 10 + (*c - '0');
    if (r < 0) {
      return 0;
    }
    *c = nb_reader_getc (I);
  } while (*c >= 0 && isdigit(*c));

  if (sgn) {
    r = -r;
  }
  *x = r;
  return 1;
}