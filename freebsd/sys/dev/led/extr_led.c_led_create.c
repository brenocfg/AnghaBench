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
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  led_t ;

/* Variables and functions */
 struct cdev* led_create_state (int /*<<< orphan*/ *,void*,char const*,int /*<<< orphan*/ ) ; 

struct cdev *
led_create(led_t *func, void *priv, char const *name)
{

	return (led_create_state(func, priv, name, 0));
}