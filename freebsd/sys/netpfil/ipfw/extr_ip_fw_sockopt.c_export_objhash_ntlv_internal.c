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
struct sockopt_data {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_obj_ntlv ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ipfw_export_obj_ntlv (struct named_object*,int /*<<< orphan*/ *) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,int) ; 

__attribute__((used)) static int
export_objhash_ntlv_internal(struct namedobj_instance *ni,
    struct named_object *no, void *arg)
{
	struct sockopt_data *sd;
	ipfw_obj_ntlv *ntlv;

	sd = (struct sockopt_data *)arg;
	ntlv = (ipfw_obj_ntlv *)ipfw_get_sopt_space(sd, sizeof(*ntlv));
	if (ntlv == NULL)
		return (ENOMEM);
	ipfw_export_obj_ntlv(no, ntlv);
	return (0);
}