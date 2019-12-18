#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_3__ {char* alias; char* desc; int value; } ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 TYPE_1__* featurelist ; 
 int /*<<< orphan*/  get_file_features (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ *) ; 
 unsigned long nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static bool
print_file_features(Elf *elf, int phcount, int fd, char *filename)
{
	u_int32_t features;
	unsigned long i;

	if (!get_file_features(elf, phcount, fd, &features, NULL)) {
		return (false);
	}

	printf("File '%s' features:\n", filename);
	for (i = 0; i < nitems(featurelist); ++i) {
		printf("%s\t\t'%s' is ", featurelist[i].alias,
		    featurelist[i].desc);

		if ((featurelist[i].value & features) == 0)
			printf("un");

		printf("set.\n");
	}
	return (true);
}