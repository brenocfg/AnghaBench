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
typedef  int UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 int DIV_REG ; 
 int /*<<< orphan*/  DKGREY ; 
 int /*<<< orphan*/  LTGREY ; 
 int /*<<< orphan*/  SOLID ; 
 int* accu ; 
 int* accua ; 
 int arand () ; 
 int /*<<< orphan*/  initarand (int) ; 
 int /*<<< orphan*/  plot (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int rand () ; 
 int seed ; 
 int /*<<< orphan*/  waitpad (int) ; 
 int /*<<< orphan*/  waitpadup () ; 

void main(void)
{
  UBYTE r, s, t, u;

  for(r = 0; r != 80; r++) {
    accu[r] = 0;
    accua[r] = 0;
  }

  /* We use the DIV register to get a random initial seed */
  puts("Getting seed");
  puts("Push any key (1)");
  waitpad(0xFF);
  waitpadup();
  seed = DIV_REG;
  puts("Push any key (2)");
  waitpad(0xFF);
  waitpadup();
  seed |= (UWORD)DIV_REG << 8;

  /* initarand() calls initrand() */
  initarand(seed);

  do {
    r = rand();
    s = arand();

    if(r < 80) {
      t = ++accu[r];
      plot(r, 144-t, LTGREY, SOLID);
    }
    if(s < 80) {
      u = ++accua[s];
      plot(s+80, 144-u, DKGREY, SOLID);
    }
  }
  while(t != 144 && u != 144); 
}