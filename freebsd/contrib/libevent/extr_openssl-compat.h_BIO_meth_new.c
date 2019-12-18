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
struct TYPE_4__ {int type; char const* name; } ;
typedef  TYPE_1__ BIO_METHOD ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static inline BIO_METHOD *BIO_meth_new(int type, const char *name)
{
	BIO_METHOD *biom = calloc(1, sizeof(BIO_METHOD));

	if (biom != NULL) {
		biom->type = type;
		biom->name = name;
	}
	return biom;
}