#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
typedef  int /*<<< orphan*/  collpri_t ;
struct TYPE_4__ {scalar_t__ pass; scalar_t__ pri; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNKNOWN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int maxpri ; 
 int numpri ; 
 TYPE_1__* prilist ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int32_t
new_pri(void)
{
	int i;

	if (numpri >= maxpri) {
		maxpri = maxpri ? maxpri * 2 : 1024;
		prilist = realloc(prilist, sizeof (collpri_t) * maxpri);
		if (prilist == NULL) {
			fprintf(stderr,"out of memory");
			return (-1);
		}
		for (i = numpri; i < maxpri; i++) {
			prilist[i].res = UNKNOWN;
			prilist[i].pri = 0;
			prilist[i].pass = 0;
		}
	}
	return (numpri++);
}