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
typedef  size_t u_int ;
struct intr_vector {size_t iv_vec; } ;

/* Variables and functions */
 int MAX_STRAY_LOG ; 
 int* intr_stray_count ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
intr_stray_vector(void *cookie)
{
	struct intr_vector *iv;
	u_int vec;

	iv = cookie;
	vec = iv->iv_vec;
	if (intr_stray_count[vec] < MAX_STRAY_LOG) {
		printf("stray vector interrupt %d\n", vec);
		intr_stray_count[vec]++;
		if (intr_stray_count[vec] >= MAX_STRAY_LOG)
			printf("got %d stray vector interrupt %d's: not "
			    "logging anymore\n", MAX_STRAY_LOG, vec);
	}
}