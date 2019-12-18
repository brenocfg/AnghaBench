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
struct indir {int shift; uintptr_t* array; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int NMASK ; 
 int md_debug ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uintptr_t
s_read(struct indir *ip, off_t offset)
{
	struct indir *cip;
	int idx;
	uintptr_t up;

	if (md_debug > 1)
		printf("s_read(%jd)\n", (intmax_t)offset);
	up = 0;
	for (cip = ip; cip != NULL;) {
		if (cip->shift) {
			idx = (offset >> cip->shift) & NMASK;
			up = cip->array[idx];
			cip = (struct indir *)up;
			continue;
		}
		idx = offset & NMASK;
		return (cip->array[idx]);
	}
	return (0);
}