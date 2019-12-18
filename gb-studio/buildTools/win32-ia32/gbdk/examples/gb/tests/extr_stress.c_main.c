#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UWORD ;
typedef  int UBYTE ;
struct TYPE_3__ {void* h; void* l; } ;
struct TYPE_4__ {int /*<<< orphan*/  w; TYPE_1__ b; } ;

/* Variables and functions */
 void* DIV_REG ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  initrand (int /*<<< orphan*/ ) ; 
 int* malloc (int) ; 
 scalar_t__ malloc_first ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int rand () ; 
 TYPE_2__ seed ; 
 int /*<<< orphan*/  waitpad (int) ; 
 int /*<<< orphan*/  waitpadup () ; 

void main(void) 
{
    UBYTE *base[32];
    UBYTE offset;
    UWORD worked = 0;
    UBYTE done = 0;
    UBYTE tests = 0;
    UWORD size;
    UWORD total = 0;

#ifdef GETSEED
    puts("Getting seed");
    puts("Push any key (1)");
    waitpad(0xFF);
    waitpadup();
    seed.b.l = DIV_REG;
    puts("Push any key (2)");
    waitpad(0xFF);
    waitpadup();
    seed.b.h = DIV_REG;

    /* initarand() calls initrand() */
    initrand(seed.w);
#endif
    printf("Testing...\n");

    /* Wipe it */
    memset(base, 0, 32*sizeof(UBYTE *));

    for (tests = 0; tests < 20; tests++) {
	/* And go... */
	done = 0;
	worked = 0;
	malloc_first = 0;

	while (!done) {
	    offset = rand()&0x1f;
	    if (base[offset] != NULL) {
		free(base[offset]);
		//		malloc_gc();
	    }
	    
	    base[offset] = malloc((UWORD)rand() + (UWORD)(rand()&0x3f));
	    if (base[offset] == NULL) {
		done = 1;
	    }
	    worked++;
	    if (!(worked&0xff)) {
		printf("%lu\r", worked);
		//		gotoxy(0, posy());
	    }
	}
	total += worked;
	printf("%lu worked.\n", worked);
    }
    printf("Total: %lu\n", total);
}