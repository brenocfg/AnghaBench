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
struct vegas {int slow_start_toggle; } ;
struct cc_var {struct vegas* cc_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_VEGAS ; 
 struct vegas* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vegas_cb_init(struct cc_var *ccv)
{
	struct vegas *vegas_data;

	vegas_data = malloc(sizeof(struct vegas), M_VEGAS, M_NOWAIT);

	if (vegas_data == NULL)
		return (ENOMEM);

	vegas_data->slow_start_toggle = 1;
	ccv->cc_data = vegas_data;

	return (0);
}