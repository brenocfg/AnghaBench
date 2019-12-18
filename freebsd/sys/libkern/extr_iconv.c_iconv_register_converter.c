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
struct kobj_class {int dummy; } ;
struct iconv_converter_class {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct iconv_converter_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_link ; 
 int /*<<< orphan*/  iconv_converters ; 
 int /*<<< orphan*/  kobj_class_compile (struct kobj_class*) ; 

__attribute__((used)) static int
iconv_register_converter(struct iconv_converter_class *dcp)
{
	kobj_class_compile((struct kobj_class*)dcp);
	dcp->refs++;
	TAILQ_INSERT_TAIL(&iconv_converters, dcp, cc_link);
	return 0;
}