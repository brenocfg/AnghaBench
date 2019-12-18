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
struct sod {int sod_major; int sod_minor; long sod_next; scalar_t__ sod_library; scalar_t__ sod_name; } ;
struct TYPE_2__ {long sdt_sods; long sdt_paths; } ;

/* Variables and functions */
 scalar_t__ align_struct (scalar_t__) ; 
 int /*<<< orphan*/ * dyn ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* sdt ; 
 scalar_t__ text_addr ; 

__attribute__((used)) static void
dump_sods(void)
{
    long sod_offset;
    long paths_offset;

    if (dyn == NULL)		/* Not a shared object */
	return;

    sod_offset = sdt->sdt_sods;
    printf("  Shared object dependencies:\n");
    while (sod_offset != 0) {
      const struct sod *sodp = (const struct sod *) align_struct((text_addr + sod_offset));
	const char *name = (const char *) (text_addr + sodp->sod_name);

	if (sodp->sod_library)
	    printf("    -l%-16s version %d.%d\n", name, sodp->sod_major,
		sodp->sod_minor);
	else
	    printf("    %s\n", name);
	sod_offset = sodp->sod_next;
    }
    paths_offset = sdt->sdt_paths;
    printf("  Shared object additional paths:\n");
    if (paths_offset != 0) {
	printf("    %s\n", (const char *)(text_addr + paths_offset));
    } else {
	printf("    (none)\n");
    }
}