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

/* Variables and functions */
 struct pt_encoder* pt_alloc_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_null (struct pt_encoder*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result alloc_encoder_null(void)
{
	struct pt_encoder *encoder;

	encoder = pt_alloc_encoder(NULL);
	ptu_null(encoder);

	return ptu_passed();
}