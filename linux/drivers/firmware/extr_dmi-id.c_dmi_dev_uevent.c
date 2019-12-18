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
struct kobj_uevent_env {int buflen; int /*<<< orphan*/ * buf; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*) ; 
 int get_modalias (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dmi_dev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	ssize_t len;

	if (add_uevent_var(env, "MODALIAS="))
		return -ENOMEM;
	len = get_modalias(&env->buf[env->buflen - 1],
			   sizeof(env->buf) - env->buflen);
	if (len >= (sizeof(env->buf) - env->buflen))
		return -ENOMEM;
	env->buflen += len;
	return 0;
}