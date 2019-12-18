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
struct ptunit_result {int dummy; } ;
struct pt_config {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;

/* Variables and functions */
 int /*<<< orphan*/ * buffer ; 
 int pt_config_from_user (struct pt_config*,struct pt_config*) ; 
 int /*<<< orphan*/  pt_config_init (struct pt_config*) ; 
 int /*<<< orphan*/  pte_bad_config ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result from_user_bad_buffer(void)
{
	struct pt_config config, user;
	int errcode;

	pt_config_init(&user);

	errcode = pt_config_from_user(&config, &user);
	ptu_int_eq(errcode, -pte_bad_config);

	user.begin = buffer;

	errcode = pt_config_from_user(&config, &user);
	ptu_int_eq(errcode, -pte_bad_config);

	user.begin = NULL;
	user.end = buffer;

	errcode = pt_config_from_user(&config, &user);
	ptu_int_eq(errcode, -pte_bad_config);

	user.begin = &buffer[1];
	user.end = buffer;

	errcode = pt_config_from_user(&config, &user);
	ptu_int_eq(errcode, -pte_bad_config);

	return ptu_passed();
}