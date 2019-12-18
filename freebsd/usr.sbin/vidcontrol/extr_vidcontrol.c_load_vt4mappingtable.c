#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* len; void* dst; int /*<<< orphan*/  src; } ;
typedef  TYPE_1__ vfnt_map_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* be16toh (void*) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (unsigned int,int) ; 
 int fread (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static vfnt_map_t *
load_vt4mappingtable(unsigned int nmappings, FILE *f)
{
	vfnt_map_t *t;
	unsigned int i;

	if (nmappings == 0)
		return (NULL);

	if ((t = calloc(nmappings, sizeof(*t))) == NULL) {
		warn("calloc");
		return (NULL);
	}

	if (fread(t, sizeof *t * nmappings, 1, f) != 1) {
		warn("read mappings");
		free(t);
		return (NULL);
	}

	for (i = 0; i < nmappings; i++) {
		t[i].src = be32toh(t[i].src);
		t[i].dst = be16toh(t[i].dst);
		t[i].len = be16toh(t[i].len);
	}

	return (t);
}