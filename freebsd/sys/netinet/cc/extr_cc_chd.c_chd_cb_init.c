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
struct chd {scalar_t__ shadow_w; } ;
struct cc_var {struct chd* cc_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_CHD ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct chd* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chd_cb_init(struct cc_var *ccv)
{
	struct chd *chd_data;

	chd_data = malloc(sizeof(struct chd), M_CHD, M_NOWAIT);
	if (chd_data == NULL)
		return (ENOMEM);

	chd_data->shadow_w = 0;
	ccv->cc_data = chd_data;

	return (0);
}