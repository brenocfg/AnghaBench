#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int to; long from; } ;
struct TYPE_4__ {int from; int to; } ;
struct TYPE_6__ {TYPE_2__ old; TYPE_1__ new; } ;

/* Variables and functions */
 scalar_t__ Aflag ; 
 int BUFSIZ ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_3__* de ; 
 scalar_t__ eflag ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* f1mark ; 
 char* f2mark ; 
 char* f3mark ; 
 int /*<<< orphan*/ * fp ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  oflag ; 
 int /*<<< orphan*/ * overlap ; 
 int /*<<< orphan*/  overlapcnt ; 
 int /*<<< orphan*/  prange (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
edscript(int n)
{
	int k;
	size_t j;
	char block[BUFSIZ];

	for (; n > 0; n--) {
		if (!oflag || !overlap[n]) {
			prange(&de[n].old);
		} else {
			printf("%da\n", de[n].old.to -1);
			if (Aflag) {
				printf("%s\n", f2mark);
				fseek(fp[1], de[n].old.from, SEEK_SET);
				for (k = de[n].old.to - de[n].old.from; k > 0; k -= j) {
					j = k > BUFSIZ ? BUFSIZ : k;
					if (fread(block, 1, j, fp[1]) != j)
						errx(2, "logic error");
					fwrite(block, 1, j, stdout);
				}
				printf("\n");
			}
			printf("=======\n");
		}
		fseek(fp[2], (long)de[n].new.from, SEEK_SET);
		for (k = de[n].new.to - de[n].new.from; k > 0; k-= j) {
			j = k > BUFSIZ ? BUFSIZ : k;
			if (fread(block, 1, j, fp[2]) != j)
				errx(2, "logic error");
			fwrite(block, 1, j, stdout);
		}
		if (!oflag || !overlap[n])
			printf(".\n");
		else {
			printf("%s\n.\n", f3mark);
			printf("%da\n%s\n.\n", de[n].old.from - 1, f1mark);
		}
	}
	if (iflag)
		printf("w\nq\n");

	exit(eflag == 0 ? overlapcnt : 0);
}