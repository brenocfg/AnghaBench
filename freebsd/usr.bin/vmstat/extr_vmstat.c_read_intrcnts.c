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
typedef  int /*<<< orphan*/  kaddr ;
typedef  int /*<<< orphan*/  intrcntlen ;
struct TYPE_2__ {scalar_t__ n_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  X_INTRCNT ; 
 size_t X_NINTRCNT ; 
 int /*<<< orphan*/  X_SINTRCNT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * kd ; 
 int /*<<< orphan*/  kread (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kreadptr (uintptr_t,unsigned long*,size_t) ; 
 unsigned long* malloc (size_t) ; 
 scalar_t__ mysysctl (char*,unsigned long*,size_t*) ; 
 TYPE_1__* namelist ; 
 unsigned long* reallocf (unsigned long*,size_t) ; 

__attribute__((used)) static unsigned int
read_intrcnts(unsigned long **intrcnts)
{
	size_t intrcntlen;
	uintptr_t kaddr;

	if (kd != NULL) {
		kread(X_SINTRCNT, &intrcntlen, sizeof(intrcntlen));
		if ((*intrcnts = malloc(intrcntlen)) == NULL)
			err(1, "malloc()");
		if (namelist[X_NINTRCNT].n_type == 0)
			kread(X_INTRCNT, *intrcnts, intrcntlen);
		else {
			kread(X_INTRCNT, &kaddr, sizeof(kaddr));
			kreadptr(kaddr, *intrcnts, intrcntlen);
		}
	} else {
		for (*intrcnts = NULL, intrcntlen = 1024; ; intrcntlen *= 2) {
			*intrcnts = reallocf(*intrcnts, intrcntlen);
			if (*intrcnts == NULL)
				err(1, "reallocf()");
			if (mysysctl("hw.intrcnt", *intrcnts, &intrcntlen) == 0)
				break;
		}
	}

	return (intrcntlen / sizeof(unsigned long));
}