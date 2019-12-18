#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int (* rndfun_t ) () ;
struct TYPE_2__ {int (* rndfun ) () ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,unsigned int,int,int,int,int) ; 
 TYPE_1__* rndfuns ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

int
main(int argc, char *argv[])
{
	uint64_t vals[4] = {};
	uint64_t avg;
	unsigned int i;
	rndfun_t f;

	if (argc == 1)
		f = rndfuns[0].rndfun;
	else {
		for (i = 0; rndfuns[i].name != NULL; i++) {
			if (strcasecmp(rndfuns[i].name, argv[1]) == 0)
				break;
		}
		if (rndfuns[i].name == NULL)
			return 1;
		f = rndfuns[i].rndfun;
	}

	for (;;) {
		vals[f() % 4]++;
		if (((i++) % (4*1024*1024)) == 0) {
			avg = vals[0] + vals[1] + vals[2] + vals[3];
			avg /= 4;
			printf("%d: %ld %ld %ld %ld\n", i, vals[0] - avg, vals[1] - avg, vals[2] - avg, vals[3] - avg);
		}
	}
	return 0;
}