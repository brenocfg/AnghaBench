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
struct pthread_attr {int dummy; } ;
typedef  int /*<<< orphan*/ * pthread_attr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _pthread_attr_default ; 
 int /*<<< orphan*/  _thr_check_init () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
_thr_attr_init(pthread_attr_t *attr)
{
	int	ret;
	pthread_attr_t	pattr;

	_thr_check_init();

	/* Allocate memory for the attribute object: */
	if ((pattr = (pthread_attr_t) malloc(sizeof(struct pthread_attr))) == NULL)
		/* Insufficient memory: */
		ret = ENOMEM;
	else {
		/* Initialise the attribute object with the defaults: */
		memcpy(pattr, &_pthread_attr_default, sizeof(struct pthread_attr));

		/* Return a pointer to the attribute object: */
		*attr = pattr;
		ret = 0;
	}
	return(ret);
}