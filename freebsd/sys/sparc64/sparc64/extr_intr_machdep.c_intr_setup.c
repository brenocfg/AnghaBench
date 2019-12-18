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
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  iv_func_t ;
typedef  int /*<<< orphan*/  ih_func_t ;
struct TYPE_2__ {int iv_pri; int iv_vec; void* iv_arg; int /*<<< orphan*/ * iv_func; } ;

/* Variables and functions */
 int MAXCOMLEN ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/ ** intr_handlers ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 TYPE_1__* intr_vectors ; 
 int /*<<< orphan*/  intrcnt_updatename (int,char*,int) ; 
 char** pil_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 

void
intr_setup(int pri, ih_func_t *ihf, int vec, iv_func_t *ivf, void *iva)
{
	char pilname[MAXCOMLEN + 1];
	register_t s;

	s = intr_disable();
	if (vec != -1) {
		intr_vectors[vec].iv_func = ivf;
		intr_vectors[vec].iv_arg = iva;
		intr_vectors[vec].iv_pri = pri;
		intr_vectors[vec].iv_vec = vec;
	}
	intr_handlers[pri] = ihf;
	intr_restore(s);
	snprintf(pilname, MAXCOMLEN + 1, "pil%d: %s", pri, pil_names[pri]);
	intrcnt_updatename(pri, pilname, 1);
}