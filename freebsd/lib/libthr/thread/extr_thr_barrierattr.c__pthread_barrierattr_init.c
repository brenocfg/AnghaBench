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
struct pthread_barrierattr {int dummy; } ;
typedef  TYPE_1__* pthread_barrierattr_t ;
struct TYPE_4__ {int /*<<< orphan*/  pshared; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 TYPE_1__* malloc (int) ; 

int
_pthread_barrierattr_init(pthread_barrierattr_t *attr)
{

	if (attr == NULL)
		return (EINVAL);

	if ((*attr = malloc(sizeof(struct pthread_barrierattr))) == NULL)
		return (ENOMEM);

	(*attr)->pshared = PTHREAD_PROCESS_PRIVATE;
	return (0);
}