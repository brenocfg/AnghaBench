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
typedef  TYPE_1__* syscon_class_t ;
struct syscon {int /*<<< orphan*/  pdev; void* softc; } ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SYSCON ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

struct syscon *
syscon_create(device_t pdev, syscon_class_t syscon_class)
{
	struct syscon *syscon;

	/* Create object and initialize it. */
	syscon = malloc(sizeof(struct syscon), M_SYSCON,
	    M_WAITOK | M_ZERO);
	kobj_init((kobj_t)syscon, (kobj_class_t)syscon_class);

	/* Allocate softc if required. */
	if (syscon_class->size > 0)
		syscon->softc = malloc(syscon_class->size, M_SYSCON,
		    M_WAITOK | M_ZERO);

	/* Rest of init. */
	syscon->pdev = pdev;
	return (syscon);
}