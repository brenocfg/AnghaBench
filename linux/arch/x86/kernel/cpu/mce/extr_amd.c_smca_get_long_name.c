#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum smca_bank_types { ____Placeholder_smca_bank_types } smca_bank_types ;
struct TYPE_2__ {char const* long_name; } ;

/* Variables and functions */
 int N_SMCA_BANK_TYPES ; 
 TYPE_1__* smca_names ; 

const char *smca_get_long_name(enum smca_bank_types t)
{
	if (t >= N_SMCA_BANK_TYPES)
		return NULL;

	return smca_names[t].long_name;
}