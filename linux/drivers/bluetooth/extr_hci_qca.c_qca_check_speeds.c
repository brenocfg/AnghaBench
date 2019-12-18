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
struct hci_uart {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QCA_INIT_SPEED ; 
 int /*<<< orphan*/  QCA_OPER_SPEED ; 
 int /*<<< orphan*/  qca_get_speed (struct hci_uart*,int /*<<< orphan*/ ) ; 
 scalar_t__ qca_is_wcn399x (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca_soc_type (struct hci_uart*) ; 

__attribute__((used)) static int qca_check_speeds(struct hci_uart *hu)
{
	if (qca_is_wcn399x(qca_soc_type(hu))) {
		if (!qca_get_speed(hu, QCA_INIT_SPEED) &&
		    !qca_get_speed(hu, QCA_OPER_SPEED))
			return -EINVAL;
	} else {
		if (!qca_get_speed(hu, QCA_INIT_SPEED) ||
		    !qca_get_speed(hu, QCA_OPER_SPEED))
			return -EINVAL;
	}

	return 0;
}