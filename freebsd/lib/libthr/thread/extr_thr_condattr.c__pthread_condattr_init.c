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
struct pthread_cond_attr {int dummy; } ;
typedef  int /*<<< orphan*/ * pthread_condattr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _pthread_condattr_default ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
_pthread_condattr_init(pthread_condattr_t *attr)
{
	pthread_condattr_t pattr;
	int ret;

	if ((pattr = (pthread_condattr_t)
	    malloc(sizeof(struct pthread_cond_attr))) == NULL) {
		ret = ENOMEM;
	} else {
		memcpy(pattr, &_pthread_condattr_default,
		    sizeof(struct pthread_cond_attr));
		*attr = pattr;
		ret = 0;
	}
	return (ret);
}