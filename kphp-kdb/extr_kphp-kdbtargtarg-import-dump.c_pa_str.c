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
 char* Pp ; 

__attribute__((used)) static inline void pa_str (void) {
  while (*Pp && (Pp[0] != '^' || Pp[1] != '*' || Pp[2] != '^') 
  	     && (Pp[0] != '%' || Pp[1] != '*' || Pp[2] != '%')) {
    if ((unsigned char) *Pp < ' ') { *Pp = ' '; }
    Pp++;
  }
  *Pp = 0;
}