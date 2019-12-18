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
typedef  int /*<<< orphan*/  va_list ;
struct protoent_data {int dummy; } ;

/* Variables and functions */
 int NS_UNAVAIL ; 
 int /*<<< orphan*/  __endprotoent_p (struct protoent_data*) ; 
 struct protoent_data* __protoent_data_init () ; 

__attribute__((used)) static int
files_endprotoent(void *retval, void *mdata, va_list ap)
{
	struct protoent_data *ped;

	if ((ped = __protoent_data_init()) == NULL)
		return (NS_UNAVAIL);

	__endprotoent_p(ped);
	return (NS_UNAVAIL);
}