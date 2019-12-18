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
struct pt_encoder {int dummy; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pt_encoder_init (struct pt_encoder*,struct pt_config*) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result encoder_init_null(void)
{
	struct pt_encoder encoder;
	struct pt_config config;
	int errcode;

	errcode = pt_encoder_init(NULL, &config);
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_encoder_init(&encoder, NULL);
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}