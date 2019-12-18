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
struct kaudit_record {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_record_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct kaudit_record*) ; 

void
audit_free(struct kaudit_record *ar)
{

	uma_zfree(audit_record_zone, ar);
}